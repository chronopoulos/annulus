#include <iostream>
#include <AudioThread.h>
#include "Annulus.h"

using namespace std;

extern bool VERBOSE;

extern Annulus annulus;

AudioThread::AudioThread(QObject* parent)
    : QThread(parent)
{

    openPCM();
    setHardwareParams();
    allocatePeriodBuffer();
    setSoftwareParams();


}

void AudioThread::openPCM(void)
{
    // open pcm device
    int err;

	//err = snd_pcm_open(&pcm_handle, "default",
    //                    SND_PCM_STREAM_PLAYBACK, 0);

	err = snd_pcm_open(&pcm_handle, "sysdefault:CARD=PCH",
                        SND_PCM_STREAM_PLAYBACK, 0);

	//err = snd_pcm_open(&pcm_handle, "sysdefault:CARD=K6",
    //                  SND_PCM_STREAM_PLAYBACK, 0);

    if (err) {
        cout << "Error in AudioThread::openPCM" << endl;
        cout << snd_strerror(err) << endl;
        exit(1);
    }
}

void AudioThread::setHardwareParams(void)
{
    int err;
	snd_pcm_hw_params_malloc(&hw_params);

	// Load hardware params structure
	snd_pcm_hw_params_any(pcm_handle, hw_params); // initialize the struct
	err = snd_pcm_hw_params_set_access(pcm_handle, hw_params,
					SND_PCM_ACCESS_RW_INTERLEAVED);
	err = snd_pcm_hw_params_set_format(pcm_handle, hw_params,
						SND_PCM_FORMAT_S16_LE); 

    nchannels = 2;
	err = snd_pcm_hw_params_set_channels(pcm_handle, hw_params, nchannels);

    unsigned int sampleRate = 44100;
    int dir = 0; // direction
    err = snd_pcm_hw_params_set_rate_near(pcm_handle, hw_params,
        &sampleRate, &dir);

	// Set hardware params
    err = snd_pcm_hw_params(pcm_handle, hw_params);
    if (err < 0) {
        cout << "Could not set hardware params; exiting." << endl;
        exit(1);
    } else {
        cout << "Hardware params set!" << endl;
    }

	snd_pcm_hw_params_free(hw_params);

}

void AudioThread::allocatePeriodBuffer(void)
{
    // set buffer and period size (near)
    nframes_buffer = 1024;
    nframes_period = 64;
    snd_pcm_hw_params_set_buffer_size_near(pcm_handle, hw_params, &nframes_buffer);
	snd_pcm_hw_params_set_period_size_near(pcm_handle, hw_params, &nframes_period, 0);

    // get buffer and period size
    snd_pcm_hw_params_get_buffer_size(hw_params, &nframes_buffer);
	snd_pcm_hw_params_get_period_size(hw_params, &nframes_period, 0);

    cout << "Buffer size: " << nframes_buffer << " frames" << endl;
    cout << "Period size: " << nframes_period << " frames" << endl;

    // allocate period buffer
    periodBuffer = (short*) malloc(nchannels*nframes_period*sizeof(short));
    // -> probably don't need to do this with snd_pcm_period_malloc() or whatever
}

void AudioThread::setSoftwareParams(void)
{
    int err = 0;
    err = snd_pcm_sw_params_malloc(&sw_params);

    // load sw_params structure
    err = snd_pcm_sw_params_current (pcm_handle, sw_params);
    //err = snd_pcm_sw_params_set_avail_min (pcm_handle, sw_params,
    //    nframes_buffer-nframes_period);
    err = snd_pcm_sw_params_set_start_threshold (pcm_handle, sw_params, nframes_period);

    // set software params
    err = snd_pcm_sw_params (pcm_handle, sw_params);
    if (err < 0) {
        cout << "Could not set software params; exiting." << endl;
        exit(1);
    } else {
        cout << "Software params set!" << endl;
    }

}


void AudioThread::run()
{

    snd_pcm_sframes_t avail, framesWritten;

    stopRequested = false;

    // reset playhead
    annulus.reset();

    snd_pcm_prepare(pcm_handle);

    cout << "Entering audio loop.." << endl;
    while(1) {

        if (stopRequested) {
            cout << "Stop Requested: breaking out of audio loop.." << endl;
            //snd_pcm_drain(pcm_handle);
            snd_pcm_drop(pcm_handle);
            break;
        }

        // might want to think about using snd_pcm_avail() here instead
        avail = snd_pcm_avail_update (pcm_handle);
        if (avail < 0) {

            cout << "snd_pcm_avail returned error: " << snd_strerror(avail) << endl;

        } else if ( (snd_pcm_uframes_t)avail > nframes_period ) {

            memset(periodBuffer, 0, nchannels*nframes_period*sizeof(short));
            annulus.getNextPeriod(periodBuffer, nframes_period);

            framesWritten = snd_pcm_writei(pcm_handle, periodBuffer, nframes_period);
            if (framesWritten < 0) {
                switch (framesWritten) {
                    case -EBADFD:
                        cout << "PCM is not in the right state" << endl;
                        break;
                    case -EPIPE:
                        cout << "an underrun occurred" << endl;
                        emit xrunOccurred();
                        break;
                    case -ESTRPIPE:
                        cout << "a suspend event occurred (stream is suspended and waiting for an application recovery)" << endl;
                        break;
                }
                break;
            } else if ((snd_pcm_uframes_t)framesWritten < nframes_period) {
                cout << "framesWritten was less that nframes_period; that's weird" << endl;
            }

        }
        sleep(0.001); // temporary solution to the CPU-railing problem

    }

}

void AudioThread::stop(void) {

    stopRequested = true;

}
