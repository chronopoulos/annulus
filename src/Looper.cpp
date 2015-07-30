#include <iostream>
#include <sndfile.h>

#include <Looper.h>

using namespace std;

extern bool VERBOSE;

Looper::Looper(QWidget* parent, QString path) : QFrame(parent) {

    this->path = path;

    loadButton = new QPushButton;
    loadButton->setFocusPolicy(Qt::NoFocus);
    QObject::connect(loadButton, SIGNAL(clicked(bool)),
        this, SLOT(browseLoops(void)));

    progressBar = new QProgressBar;
    progressBar->setTextVisible(false);

    knob = new QDial;
    knob->setFocusPolicy(Qt::NoFocus);
    QObject::connect(knob, SIGNAL(valueChanged(int)),
        this, SLOT(adjustVolume(int)));
    volume = 0.5;
    knob->setValue(50);
    knob->setMaximumWidth(50);

    activateCheckBox = new QCheckBox;
    activateCheckBox->setFocusPolicy(Qt::NoFocus);
    QObject::connect(activateCheckBox, SIGNAL(toggled(bool)),
        this, SLOT(toggleActive(bool)));

    conductorCheckBox = new QCheckBox;
    conductorCheckBox->setFocusPolicy(Qt::NoFocus);
    conductorCheckBox->setAutoExclusive(true);
    QObject::connect(conductorCheckBox, SIGNAL(toggled(bool)),
        this, SLOT(toggleConductor(bool)));

    layout = new QGridLayout;
    layout->addWidget(loadButton, 0,0, 2,1);
    layout->addWidget(progressBar, 1,0, 2,1);
    layout->addWidget(activateCheckBox, 0,2, 1,1);
    layout->addWidget(conductorCheckBox, 0,3, 1,1);
    layout->addWidget(knob, 1,2, 2,2);

    this->setLayout(layout);

    this->setMinimumHeight(110);
    //this->setMinimumWidth(250);

    this->setFrameStyle(QFrame::Panel | QFrame::Raised);
    this->setLineWidth(2);

    importFile();

    progressBarInterval = 4410; // 10 Hz

    // this needs to be a signal/slot because AudioThread calls getNextSample
    QObject::connect(this, SIGNAL(progressBarUpdated(int)),
        this, SLOT(updateProgressBar(int)));

    isPrimed= false;
    isDeprimed= false;
    isActive = false;
    isConductor = false;

}

void Looper::browseLoops(void) {

    QString tmpPath = QFileDialog::getOpenFileName(this, "Select Loop",
                        "/home/chrono/music/samples/loops/annulus");
    if (!tmpPath.isNull()) {
        path = tmpPath;
        importFile();
    }

}

void Looper::importFile() {

    SF_INFO info;
    SNDFILE* sf = sf_open(path.toStdString().c_str(), SFM_READ, &info);
    if (sf == NULL){
        cout << "Could not open file: " << path.toStdString() << endl;
        exit(-1);
    }

    nframes = info.frames;
    nchannels = info.channels;
    sampleBuffer = (short*) malloc(nframes*nchannels*sizeof(short));
    int numRead = sf_read_short(sf, sampleBuffer, nframes*nchannels);
    if (numRead < nframes*nchannels) {
        cout << "File import failed" << endl;
        exit(-1);
    }
    sf_close(sf);
    QStringList path_split = path.split("/");
    filename = path_split.at(path_split.size()-1);

    nextIndex = 0;
    loadButton->setText(filename);
    progressBar->setMaximum(nframes);

}

short Looper::getNextSample(void) {

    tmpSample = sampleBuffer[nextIndex]*volume;

    if (++nextIndex == nframes*nchannels) {
        nextIndex = 0;
        if (isDeprimed) {
            isActive = false;
            isDeprimed = false;
        } else if (isConductor) {
            emit loopedAsConductor();
        }
    }

    if ( (nextIndex % progressBarInterval) == 0) {
        emit progressBarUpdated(nextIndex/nchannels);
    }

    return tmpSample;
}

void Looper::reset(void) {

    nextIndex = 0;

}

void Looper::updateProgressBar(int val) {

    progressBar->setValue(val);

}

void Looper::adjustVolume(int val) {

    volume = val/100.;

}

QCheckBox* Looper::getConductorCheckBox(void) {

    return conductorCheckBox;

}

void Looper::toggleActive(bool enable) {

    if (enable) {
        isPrimed = true;
        if (isConductor) {
            isActive = true;
        }
    } else {
        if (isActive) {
            isDeprimed = true;
        } else {
            isActive = false;
            isPrimed= false;
        }
    }

}

void Looper::toggleConductor(bool enable) {

    if (enable) {
        isConductor = true;
    } else {
        isConductor = false;
    }

}

void Looper::handleConductorLoop(void) {

    if (isConductor) {
        return;
    } else {
        if (isPrimed) {
            reset();
            isPrimed = false;
            isActive = true;
        }
    }

}

