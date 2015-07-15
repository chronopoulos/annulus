#include <iostream>
#include <AudioThread.h>

using namespace std;

AudioThread::AudioThread(QObject* parent, vector<Looper*>* a_loopers)
    : QThread(parent)
{

    loopers = a_loopers;

    openPCM();
    setHardwareParams();
    allocatePeriodBuffer();
    setSoftwareParams();

    snd_pcm_prepare(pcm_handle);
    snd_pcm_start(pcm_handle);
    cout << endl << "PCM prepared and started!" << endl;

}

void AudioThread::openPCM(void)
{
    // open pcm device
	snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
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
    // get buffer and period size
    snd_pcm_hw_params_get_buffer_size(hw_params, &nframes_buffer);
	snd_pcm_hw_params_get_period_size(hw_params, &nframes_period, 0);

    // allocate period buffer
    periodBuffer = (short*) malloc(nchannels*nframes_period*sizeof(short));
    // -> probably don't need to do this with snd_pcm_period_malloc() or whatever
}

void AudioThread::setSoftwareParams(void)
{
    int err;
    err = snd_pcm_sw_params_malloc(&sw_params);

    // load sw_params structure
    err = snd_pcm_sw_params_current (pcm_handle, sw_params);
    err = snd_pcm_sw_params_set_avail_min (pcm_handle, sw_params,
        nframes_buffer-nframes_period);
    err = snd_pcm_sw_params_set_start_threshold (pcm_handle, sw_params, 0U);

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

    snd_pcm_sframes_t avail;
    unsigned int frameIndex_period;

    while(1) {

        if (loopers->size() > 0) {
            if (loopers->at(0)->loaded) {
                if ((snd_pcm_wait (pcm_handle, 1000)) < 0) {
                        fprintf (stderr, "poll failed (%s)\n", strerror (errno));
                        break;
                }

                /* find out how much space is available for playback data */

                if ((avail = snd_pcm_avail_update (pcm_handle)) < 0) {
                    if (avail == -EPIPE) {
                        fprintf (stderr, "an xrun occured\n");
                        break;
                    } else {
                        fprintf (stderr, "unknown ALSA avail update return value (%d)\n", 
                             (int)avail);
                        break;
                    }
                } else {
                    if ( (snd_pcm_uframes_t)avail > nframes_period ) {
                        for (frameIndex_period = 0; frameIndex_period< nframes_period; frameIndex_period++) {
                            periodBuffer[2*frameIndex_period] = loopers->at(0)->getNextSample();
                            periodBuffer[2*frameIndex_period+1] = loopers->at(0)->getNextSample();
                        }
                        if (snd_pcm_writei(pcm_handle, periodBuffer, nframes_period) == -EPIPE) {
                            printf("XRUN.\n");
                        }
                    }
                }

            }
        } else {
            sleep(0.01);
        } 


    }

}
