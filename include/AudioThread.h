#include <alsa/asoundlib.h>
#include <QtGui>
#include <QtCore>
#include "Looper.h"

using namespace std;

class AudioThread : public QThread
{

    Q_OBJECT

    public:
        AudioThread(QObject*, vector<Looper*>*);
        void run(void);

    public slots:
        void stop(void);

    private:
        vector<Looper*>* loopers;

        snd_pcm_t* pcm_handle;
        snd_pcm_hw_params_t* hw_params;
        snd_pcm_sw_params_t* sw_params;

        unsigned int nchannels;
        snd_pcm_uframes_t nframes_buffer;
        snd_pcm_uframes_t nframes_period;
        short* periodBuffer;

        void openPCM(void);
        void setHardwareParams(void);
        void allocatePeriodBuffer(void);
        void setSoftwareParams(void);

        bool stopRequested;

    signals:
        void xrunOccurred(void);

};
