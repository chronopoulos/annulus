#include <QPushButton>
#include <QString>

class Looper : public QPushButton
{
    Q_OBJECT

    public:
        Looper();
        ~Looper();

        QString filename;
        int nframes;
        int nchannels;
        short* sampleBuffer;

    public slots:
        void importFile();

};
