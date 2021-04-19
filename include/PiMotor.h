<<<<<<< HEAD
#ifndef PIMOTOR_H
#define PIMOTOR_H

#include <pigpio.h>
#include <mutex>
#include <iostream>
using namespace std;

class PiMotor {
   private:
      int fPin;
      int rPin;
      bool DEBUG = true;
   
  public:
      PiMotor(int, int);
      void Run_left (int,bool);
      void Run_right (int,bool);
   
      int Stop_left();
      int Stop_right();
=======
/* 
 * File:   PiMotor.h
 * Author: Jin Tao
 *
 * Created on 07 April 2021, 01:13
 */

#ifndef PIMOTOR_H
#define PIMOTOR_H
#include <stdint.h>
#include <functional>
class PiMotor {
private:
    int fPin;
    int rPin;
    //int speed;
    //bool direction;
    bool DEBUG = true;
    //std::function<void()> function;
   
  public:
      // void call()
      // { 
      //   function();  // Calls the function
      //  }
      PiMotor(int, int);
      void Thread_run_left (int ,bool);
      void Thread_run_right (int,bool);
   
      int Thread_stop_left();
      int Thread_stop_right();
>>>>>>> b77243b2de3386637ade7d9cbdea8aa7800aa470
      void setDebug(bool); 
   
   /*
      This function establishes a rotary encoder on gpioA and gpioB.

      When the encoder is turned the callback function is called.
   */
<<<<<<< HEAD
};
#endif
=======

};



typedef int (*re_decoderCB_t)(int);
int callback_left(int);
int callback_right(int);
class re_decoder
{
   int mygpioA, mygpioB, levA, levB, lastGpio;

   re_decoderCB_t mycallback;

   void _pulse(int gpio, int level, uint32_t tick);

   /* Need a static callback to link with C. */
   static void _pulseEx(int gpio, int level, uint32_t tick, void *user);


   public:

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
#endif /* PIMOTOR_H */
>>>>>>> b77243b2de3386637ade7d9cbdea8aa7800aa470
