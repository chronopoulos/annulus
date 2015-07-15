#include <QPushButton>
#include <QString>

class Looper : public QPushButton
{
    Q_OBJECT

    public:
        Looper();
        ~Looper();
        bool loaded;
        short getNextSample(void);

    public slots:
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
