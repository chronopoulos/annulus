#include <QPushButton>
#include <QString>

class Looper : public QPushButton
{
    Q_OBJECT

    public:
        Looper(QString);
        short getNextSample(void);
        void reset(void);

    public slots:
        void browseLoops(void);
        void importFile(void);

    private:
        QString path;
        QString filename;
        int nframes;
        int nchannels;
        short* sampleBuffer;
        int nextIndex;
        short tmpSample;

};
