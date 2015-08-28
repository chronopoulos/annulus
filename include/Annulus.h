#ifndef ANNULUS_H
#define ANNULUS_H

#include <iostream>
#include <QString>
#include "Looper.h"
#include "Counter.h"
#include <alsa/asoundlib.h>

// this class is derived from QObject in order to enable signal forwarding,
//  which is used in the master-slave topology
#include <QtGui>

using namespace std;

class Annulus : public QObject
{

    Q_OBJECT

    public:
        Annulus(void);
        void getNextPeriod(short*, snd_pcm_uframes_t);
        void addLoopers(QStringList, QWidget*);

        Looper* getLooper(int);
        int getNLoopers(void);
        void reset(void);
        void toggleLooperByIndex(int);


    private:
        QMutex* mutex;
        vector<Looper*>* loopers;
        int nloopers;
        unsigned int frameIndex;

        QButtonGroup* masterButtonGroup;

        short* frameBuff;

        Counter* counter;

    signals:
        void masterLooped(void);

};

#endif
