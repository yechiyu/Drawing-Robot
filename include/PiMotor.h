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
      int speed;
      bool direction;
      bool DEBUG = true;
   
  public:
      PiMotor(int, int,int,bool);
      void Run_left ();
      void Run_right ();
   
      int Stop_left();
      int Stop_right();
      void setDebug(bool); 

      int pos1;
      int pos2;
   
   /*
      This function establishes a rotary encoder on gpioA and gpioB.

      When the encoder is turned the callback function is called.
   */
};
#endif
