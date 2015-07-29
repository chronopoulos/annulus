#include <iostream>
#include <sndfile.h>
#include "Annulus.h"

using namespace std;

extern bool VERBOSE;

Annulus::Annulus(void) {

    mutex = new QMutex;

    QMutexLocker locker(mutex);

    loopers = new vector<Looper*>();
    nloopers = 0;

}

void Annulus::getNextPeriod(short* buff, snd_pcm_uframes_t nframes_period) {

    QMutexLocker locker(mutex);

    for (frameIndex = 0; frameIndex < nframes_period; frameIndex++) {
        for (vector<Looper*>::iterator looper = loopers->begin(); looper != loopers->end(); looper++) {
            buff[2*frameIndex] += (*looper)->getNextSample();
            buff[2*frameIndex+1] += (*looper)->getNextSample();
        }
    }

}

void Annulus::addLoopers(QStringList pathList, QWidget* parent) {

    QMutexLocker locker(mutex);

    for (int i=0; i<pathList.size(); i++) {
        loopers->push_back(new Looper(parent, pathList.at(i)));
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
