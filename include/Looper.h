#include <QtGui>

class Looper : public QFrame
{
    Q_OBJECT

    public:
        Looper(QWidget*, QString);
        short getNextSample(void);
        void reset(void);

    public slots:
        void browseLoops(void);
        void importFile(void);
        void updateProgressBar(int);

    private:
        QPushButton* loadButton;
        QProgressBar* progressBar;
        QDial* knob;

        QGridLayout* layout;

        QString path;
        QString filename;
        int nframes;
        int nchannels;
        short* sampleBuffer;
        int nextIndex;
        short tmpSample;

        int progressBarInterval;

    signals:
        void progressBarUpdated(int);

};
