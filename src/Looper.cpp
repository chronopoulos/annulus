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

    activationButton = new ActivationButton;
    activationButton->setFocusPolicy(Qt::NoFocus);
    QObject::connect(activationButton, SIGNAL(clicked(bool)),
    //    this, SLOT(handleActivationButton(bool)));
        this, SLOT(toggleState(void)));
    // need reciprocal signal-slot relationship so that we're not drawing outside the GUI thread
    // note: this could be one connection if we register the looperstate_t enum with the meta-object system
    QObject::connect(this, SIGNAL(deactivated(void)),
        activationButton, SLOT(setInactive(void)));
    QObject::connect(this, SIGNAL(deprimed(void)),
        activationButton, SLOT(setDeprimed(void)));
    QObject::connect(this, SIGNAL(primed(void)),
        activationButton, SLOT(setPrimed(void)));
    QObject::connect(this, SIGNAL(activated(void)),
        activationButton, SLOT(setActive(void)));

    masterButton = new QPushButton("Master");
    masterButton->setFocusPolicy(Qt::NoFocus);
    QObject::connect(masterButton, SIGNAL(clicked(void)),
        this, SLOT(handleMasterButton(void)));

    layout = new QGridLayout;
    layout->addWidget(loadButton, 0,0, 2,1);
    layout->addWidget(progressBar, 1,0, 2,1);
    layout->addWidget(activationButton, 0,2, 1,1);
    layout->addWidget(masterButton, 0,3, 1,1);
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

    state = STATE_INACTIVE;

}

void Looper::browseLoops(void) {

    QString tmpPath = QFileDialog::getOpenFileName(this, "Select Loop",
                        "/home/chrono/music/samples/loops/annulus");
    if (!tmpPath.isNull()) {
        path = tmpPath;
        importFile();
    }

}

bool Looper::isPlaying(void) {

    return (state==STATE_ACTIVE) || (state==STATE_DEPRIMED);

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

void Looper::getNextFrame(short* frameBuffer) {

    for (int i=0; i<nchannels; i++) {
        *(frameBuffer+i) = sampleBuffer[nchannels*frameIndex+i]*volume;
    }

    if ( (frameIndex % progressBarInterval) == 0) {
        emit progressBarUpdated(frameIndex);
    }

    // check for loop
    if (++frameIndex == nframes) {
        frameIndex = 0;
    }



}

void Looper::transition(void) {

    if (state == STATE_PRIMED) {

        state = STATE_ACTIVE;
        emit activated();

    } else if (state == STATE_DEPRIMED) {

        state = STATE_INACTIVE;
        emit deactivated();

    }

}

void Looper::reset(void) {

    frameIndex = 0;
    transition();
    emit progressBarUpdated(frameIndex);

}

void Looper::updateProgressBar(int val) {

    progressBar->setValue(val);

}

void Looper::adjustVolume(int val) {

    volume = val/100.;

}

void Looper::handleMasterButton(void) {

    emit becameMaster(nframes);

}

void Looper::toggleState(void) {

    // see "state-square" logic for explanation

        switch (state) {
            case STATE_INACTIVE:
                state = STATE_PRIMED;
                emit primed();
                break;
            case STATE_DEPRIMED:
                state = STATE_ACTIVE;
                emit activated();
                break;
            case STATE_PRIMED:
                state = STATE_INACTIVE;
                emit deactivated();
                break;
            case STATE_ACTIVE:
                state = STATE_DEPRIMED;
                emit deprimed();
                break;
        }

}

