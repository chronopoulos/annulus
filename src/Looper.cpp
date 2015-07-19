#include <iostream>
#include <sndfile.h>

#include <Looper.h>

using namespace std;

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

    layout = new QGridLayout;
    layout->addWidget(loadButton, 0,0, 2,1);
    layout->addWidget(progressBar, 1,0, 2,1);
    layout->addWidget(knob, 0,2, 2,2);

    this->setLayout(layout);

    this->setMinimumHeight(110);
    //this->setMinimumWidth(250);

    this->setFrameStyle(QFrame::Panel | QFrame::Raised);
    this->setLineWidth(2);

    importFile();

    progressBarInterval = 4410; // 10 Hz

    QObject::connect(this, SIGNAL(progressBarUpdated(int)),
        this, SLOT(updateProgressBar(int)));

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

    tmpSample = sampleBuffer[nextIndex];
    if (++nextIndex == nframes*nchannels) {
        nextIndex = 0;
        cout << "Looper looped!" << endl;
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

