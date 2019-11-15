/*
  horgand - a organ software

  jackoutput.C  -   jack output
  Copyright (C) 2003-2004 Josep Andreu (Holborn)
  Author: Josep Andreu

  This program is free software; you can redistribute it and/or modify
  it under the terms of version 2 of the GNU General Public License
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License (version 2) for more details.

  You should have received a copy of the GNU General Public License
(version2)
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/

#include <jack/jack.h>
#include "jackoutput.h"
#include "Holrgan.h"


pthread_mutex_t jmutex;


jack_client_t *jackclient;
jack_port_t *outport_left, *outport_right;

int jackprocess(jack_nframes_t nframes, void *arg);
void jackaudioprepare();

HOR *JackOUT;


int JACKstart(HOR *hor_)
{

    JackOUT = hor_;
    jackclient = jack_client_open("Horgand", JackNoStartServer, nullptr);
    if (jackclient == 0) {
        fprintf(stderr, "Cannot make a jack client, back to Alsa\n");
        return (2);
    };
    JackOUT->SAMPLE_RATE = DSAMPLE_RATE;
    fprintf(stderr, "Internal SampleRate   = %d\nJack Output SampleRate= %d\n",
            JackOUT->SAMPLE_RATE, jack_get_sample_rate(jackclient));
    if ((unsigned int)jack_get_sample_rate(jackclient) != (unsigned int)JackOUT->SAMPLE_RATE)
        fprintf(stderr, "Adjusting SAMPLE_RATE to jackd.\n");

    JackOUT->SAMPLE_RATE = jack_get_sample_rate(jackclient);
    JackOUT->PERIOD = jack_get_buffer_size(jackclient);
    JackOUT->Put_Period();

    jack_set_process_callback(jackclient, jackprocess, 0);

    outport_left = jack_port_register(jackclient, "out_1", JACK_DEFAULT_AUDIO_TYPE,
                                      JackPortIsOutput | JackPortIsTerminal, 0);
    outport_right = jack_port_register(jackclient, "out_2", JACK_DEFAULT_AUDIO_TYPE,
                                       JackPortIsOutput | JackPortIsTerminal, 0);


    if (jack_activate(jackclient)) {
        fprintf(stderr, "Cannot activate jack client, back to Alsa\n");
        return (2);
    };

    jack_connect(jackclient, jack_port_name(outport_left), "alsa_pcm:playback_1");
    jack_connect(jackclient, jack_port_name(outport_right), "alsa_pcm:playback_2");


    pthread_mutex_init(&jmutex, NULL);

    return 3;
};


int jackprocess(jack_nframes_t nframes, void *arg)

{

    int i;

    jack_default_audio_sample_t *outl =
        (jack_default_audio_sample_t *)jack_port_get_buffer(outport_left,
                                                            JackOUT->PERIOD);
    jack_default_audio_sample_t *outr =
        (jack_default_audio_sample_t *)jack_port_get_buffer(outport_right,
                                                            JackOUT->PERIOD);


    // memset(outl, 0, nframes * sizeof(jack_default_audio_sample_t));
    // memset(outr, 0, nframes * sizeof(jack_default_audio_sample_t));


    pthread_mutex_lock(&jmutex);
    JackOUT->Alg1s(JackOUT->PERIOD, 0);
    for (i = 0; i < JackOUT->PERIOD; i += 2) {
        outl[i] = JackOUT->buf[i] * JackOUT->Master_Volume;
        outr[i] = JackOUT->buf[i + 1] * JackOUT->Master_Volume;
    }
    pthread_mutex_unlock(&jmutex);

    return (0);
};


void JACKfinish()
{
    jack_client_close(jackclient);
}
