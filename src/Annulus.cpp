#include <iostream>
#include <sndfile.h>
#include "Annulus.h"

using namespace std;

extern bool VERBOSE;

Annulus::Annulus(void) : QObject() {

    mutex = new QMutex;

    QMutexLocker locker(mutex);

    loopers = new vector<Looper*>();
    nloopers = 0;

    counter = new Counter;

    masterButtonGroup = new QButtonGroup;
    masterButtonGroup->setExclusive(true);

}

void Annulus::getNextPeriod(short* buff, snd_pcm_uframes_t nframes_period) {
    //  buff should point to a buffer of shorts which has been memset to zero

    QMutexLocker locker(mutex);

    short frameBuff[2];

    for (frameIndex = 0; frameIndex < nframes_period; frameIndex++) {
        counter->increment();
        bool loop = counter->isReset();
        for (vector<Looper*>::iterator looper = loopers->begin(); looper != loopers->end(); looper++) {
            if (loop) (*looper)->reset();
            if ((*looper)->isPlaying()) {
                (*looper)->getNextFrame(frameBuff);
                buff[2*frameIndex] += *frameBuff;
                buff[2*frameIndex+1] += *(frameBuff+1);
            }
        }
    }

}

void Annulus::addLoopers(QStringList pathList, QWidget* parent) {

    QMutexLocker locker(mutex);

    Looper* tmpLooper;
    for (int i=0; i<pathList.size(); i++) {

        tmpLooper = new Looper(parent, pathList.at(i));
        loopers->push_back(tmpLooper);
        masterButtonGroup->addButton(tmpLooper->masterButton);


        QObject::connect(tmpLooper, SIGNAL(becameMaster(int)),
            counter, SLOT(setLength(int)));
        
        if (loopers->size()==1) tmpLooper->toggleMaster(true);
    }

}

int Annulus::getNLoopers(void) {

    QMutexLocker locker(mutex);

    return loopers->size();

}

Looper* Annulus::getLooper(int i) {

    QMutexLocker locker(mutex);

    return loopers->at(i);

}

void Annulus::reset(void) {

    QMutexLocker locker(mutex);

    counter->reset();

    for (vector<Looper*>::iterator looper = loopers->begin(); looper != loopers->end(); looper++) {
        (*looper)->reset();
    }

}

void Annulus::toggleLooperByIndex(int i) {

    if (getNLoopers() > i) {
        QMutexLocker locker(mutex);
        loopers->at(i)->toggleState();
    }

}
