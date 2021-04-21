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
      void setDebug(bool); 
   
   /*
      This function establishes a rotary encoder on gpioA and gpioB.

      When the encoder is turned the callback function is called.
   */
};
void Pi_servo(int Fre);
#endif
