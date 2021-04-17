/* 
 * File:   PiMotor.h
 * Author: Steve McMillan
 *
 * Created on 07 July 2017, 17:13
 */

#ifndef PIMOTOR_H
#define PIMOTOR_H
#include <stdint.h>

typedef int (*re_decoderCB_t)(int);
int callback_left(int);
int callback_right(int);
class PiMotor {
private:
    int fPin;
    int rPin;
    int speed;
    bool direction;
    bool DEBUG = false;
    int mygpioA, mygpioB, levA, levB, lastGpio;

    re_decoderCB_t mycallback;

    void _pulse(int gpio, int level, uint32_t tick);

   /* Need a static callback to link with C. */
   static void _pulseEx(int gpio, int level, uint32_t tick, void *user);
  public:
      PiMotor(int, int,int,bool);
      // void Thread_run_left ();
      void Thread_run_right ();
      void runForMS_left( int milliseconds);
      void runForMS_right(int milliseconds);
      int *stop();
      void setDebug(bool); 
      void re_decoder(int, int,re_decoderCB_t);
   /*
      This function establishes a rotary encoder on gpioA and gpioB.

      When the encoder is turned the callback function is called.
   */

   void re_cancel(void);
   /*
      This function releases the resources used by the decoder.
   */
};

#endif /* PIMOTOR_H */
