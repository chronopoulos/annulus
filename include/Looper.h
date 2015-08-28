#ifndef LOOPER_H
#define LOOPER_H 
#include <QtGui>
#include "ActivationButton.h"

enum looperstate_t {STATE_INACTIVE, STATE_DEPRIMED, STATE_PRIMED, STATE_ACTIVE};

class Looper : public QFrame
{
    Q_OBJECT

    public:
        Looper(QWidget*, QString);
        short getNextSample(void);
        void getFirstFrame(short*);
        void getNextFrame(short*);
        void reset(void);
        QString path;
        QString filename;
        bool isPlaying(void);
        void transition(void);
        QPushButton* masterButton;

    public slots:
        void browseLoops(void);
        void importFile(void);
        void updateProgressBar(int);
        void adjustVolume(int);
        void toggleState(void);
        void toggleMaster(bool);
        void handleLockButton(void);

    private:
        QPushButton* loadButton;
        QProgressBar* progressBar;
        QDial* knob;
        ActivationButton* activationButton;
        QPushButton* lockButton;
        QGridLayout* layout;

        bool isMaster;

        looperstate_t state;

        float volume;

        int nframes;
        int nchannels;
        short* sampleBuffer;
        int nextIndex;
        int frameIndex;
        short tmpSample;

        int progressBarInterval;

    signals:
        void progressBarUpdated(int);
        void deactivated(void);
        void deprimed(void);
        void primed(void);
        void activated(void);
        void becameMaster(int);

};

#endif
