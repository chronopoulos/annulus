#ifndef LOOPER_H
#define LOOPER_H

#include <QtGui>

class Looper : public QFrame
{
    Q_OBJECT

    public:
        Looper(QWidget*, QString);
        short getNextSample(void);
        void reset(void);
        QCheckBox* getConductorCheckBox(void);
        bool isPrimed;
        bool isDeprimed;
        bool isActive;
        bool isConductor;
        QString path;
        QString filename;

    public slots:
        void browseLoops(void);
        void importFile(void);
        void updateProgressBar(int);
        void adjustVolume(int);
        void toggleActive(bool);
        void toggleConductor(bool);
        void handleConductorLoop(void);


    private:
        QPushButton* loadButton;
        QProgressBar* progressBar;
        QDial* knob;
        QCheckBox* activateCheckBox;
        QCheckBox* conductorCheckBox;

        float volume;

        QGridLayout* layout;

        int nframes;
        int nchannels;
        short* sampleBuffer;
        int nextIndex;
        short tmpSample;

        int progressBarInterval;

    signals:
        void progressBarUpdated(int);
        void loopedAsConductor(void);

};

#endif
