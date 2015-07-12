#include <iostream>
#include <sndfile.h>

#include <QPushButton>
#include <QFileDialog>
#include <QObject>

#include <Looper.h>

using namespace std;

Looper::Looper() : QPushButton("(click to load loop)") {

    QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(importFile()));

}

Looper::~Looper() {
    //free(sampleBuffer);  // commented out to prevent segfault
}

void Looper::importFile(void) {

    filename = QFileDialog::getOpenFileName(this, "Select Loop", "/home/chrono/music/samples");

    if (!filename.isNull()) {
        SF_INFO info;
        SNDFILE* sf = sf_open(filename.toStdString().c_str(), SFM_READ, &info);
        if (sf == NULL){
            cout << "Could not open file: " << filename.toStdString() << endl;
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
    }

    this->setText("loaded");

}
