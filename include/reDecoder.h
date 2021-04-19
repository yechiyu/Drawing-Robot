#ifndef REDECODER_H
#define REDECODER_H

#include <pigpio.h>
#include <iostream>
using namespace std;

typedef int (*re_decoderCB_t)(int);
int callback_left(int);
int callback_right(int);

class re_decoder
{
    private:
        int mygpioA, mygpioB, levA, levB, lastGpio;
        void _pulse(int gpio, int level, uint32_t tick);
        /* Need a static callback to link with C. */
        static void _pulseEx(int gpio, int level, uint32_t tick, void *user);


   public:
        re_decoderCB_t mycallback;
        re_decoder(int gpioA, int gpioB, re_decoderCB_t callback);
        /*
            This function establishes a rotary encoder on gpioA and gpioB.
            When the encoder is turned the callback function is called.
        */
        void encoder_left(int,int,re_decoderCB_t);
        void encoder_right(int,int,re_decoderCB_t);
        void re_cancel(void);
        /*
            This function releases the resources used by the decoder.
        */
};
#endif