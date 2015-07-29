#ifndef ANNULUS_H
#define ANNULUS_H

#include <iostream>
#include <QString>
#include "Looper.h"
#include <alsa/asoundlib.h>

using namespace std;

class Annulus
{
    public:
        Annulus(void);
        void getNextPeriod(short*, snd_pcm_uframes_t);
        void addLoopers(QStringList, QWidget*);

        Looper* getLooper(int);
        int getNLoopers(void);
        void reset(void);


    private:
        QMutex* mutex;
        vector<Looper*>* loopers;
        int nloopers;
        unsigned int frameIndex;

};

#endif
