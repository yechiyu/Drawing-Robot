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
    int speed;
    bool direction;
    bool DEBUG = true;
    //std::function<void()> function;
   
  public:
      // void call()
      // { 
      //   function();  // Calls the function
      //  }
      PiMotor(int, int,int,bool);
      void Thread_run_left ();
      void Thread_run_right ();
   
      int Thread_stop_left();
      int Thread_stop_right();
      void setDebug(bool); 
   
   /*
      This function establishes a rotary encoder on gpioA and gpioB.

      When the encoder is turned the callback function is called.
   */

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
