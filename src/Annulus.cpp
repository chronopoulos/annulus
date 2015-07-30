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

    conductorButtonGroup = new QButtonGroup;

}

void Annulus::getNextPeriod(short* buff, snd_pcm_uframes_t nframes_period) {
    //  buff should point to a buffer of shorts which has been memset to zero

    QMutexLocker locker(mutex);

    for (frameIndex = 0; frameIndex < nframes_period; frameIndex++) {
        for (vector<Looper*>::iterator looper = loopers->begin(); looper != loopers->end(); looper++) {
            if ((*looper)->isActive) {
                buff[2*frameIndex] += (*looper)->getNextSample();
                buff[2*frameIndex+1] += (*looper)->getNextSample();
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
        conductorButtonGroup->addButton(tmpLooper->getConductorCheckBox());

        // conductor topology: all to all
        QObject::connect(tmpLooper, SIGNAL(loopedAsConductor(void)),
            this, SIGNAL(conductorLooped(void)));
        QObject::connect(this, SIGNAL(conductorLooped(void)),
            tmpLooper, SLOT(handleConductorLoop(void)));
        
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

    for (vector<Looper*>::iterator looper = loopers->begin(); looper != loopers->end(); looper++) {
        (*looper)->reset();
    }

}
