#include <iostream>
#include <sndfile.h>

#include <QPushButton>
#include <QFileDialog>
#include <QObject>

#include <Looper.h>

using namespace std;

Looper::Looper(QString path) : QPushButton() {

    this->setFocusPolicy(Qt::NoFocus);
    this->path = path;
    importFile();
    QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(browseLoops(void)));
}

void Looper::browseLoops(void) {

    QString tmpPath = QFileDialog::getOpenFileName(this, "Select Loop", "/home/chrono/music/samples");
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
    this->setText(filename);

}

short Looper::getNextSample(void) {

    tmpSample = sampleBuffer[nextIndex];
    if (++nextIndex == nframes*nchannels) {
        nextIndex = 0;
        cout << "Looper looped!" << endl;
    }
    return tmpSample;

}

void Looper::reset(void) {

    nextIndex = 0;

}
