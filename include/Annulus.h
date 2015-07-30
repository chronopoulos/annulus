#ifndef ANNULUS_H
#define ANNULUS_H

#include <iostream>
#include <QString>
#include "Looper.h"
#include <alsa/asoundlib.h>

// this class is derived from QObject in order to enable signal forwarding,
//  which is used in the conductor topology
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


    private:
        QMutex* mutex;
        vector<Looper*>* loopers;
        int nloopers;
        unsigned int frameIndex;

        QButtonGroup* conductorButtonGroup;

    signals:
        void conductorLooped(void);

};

#endif
