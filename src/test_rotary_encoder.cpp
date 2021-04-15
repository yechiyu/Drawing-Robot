#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include "rotary_encoder.hpp"
#include "../include/PiMotor.h"
/*
REQUIRES

A rotary encoder contacts A and B connected to separate gpios and
the common contact connected to Pi ground.

TO BUILD

g++ -o rot_enc_cpp test_rotary_encoder.cpp rotary_encoder.cpp PiMotor.cpp -lpigpio -I../include -lrt

TO RUN

sudo ./rot_enc_cpp

*/

// int callback(int way)
// {
//    static int pos = 0;

//    pos += way;

//    std::cout << "pos=" << pos << std::endl;
//    return pos;
// }

// int main(int argc, char *argv[])
// {
//    if (gpioInitialise() < 0) return 1;

//    re_decoder dec(7, 8, callback);

//    sleep(3);

//    dec.re_cancel();

//    gpioTerminate();
// }

// int pos_left = 0;
// int pos_right = 0;

int callback_left(int way)
{
   static int pos_left = 0;
   pos_left += way;
   std::cout << "pos_left=" << pos_left << std::endl;
   return pos_left;
}

int callback_right(int way)
{
   static int pos_right = 0;
   pos_right += way;
   //std::cout << "pos_left=" << pos_right << std::endl;
   return pos_right;
}

   
int main(int argc, char *argv[])
{
   if (gpioInitialise() < 0) return 1;
   int SAMPLETIME=3000;// 3 sencond
   gpioSetPullUpDown(26, PI_PUD_UP); // Sets a pull-up.
   gpioSetPullUpDown(12, PI_PUD_UP); // Sets a pull-up.
   int m1_A = 20; //Motor 1 Forward
   int m1_B = 21; //Motor 1 Reverse
   int m2_A = 6; //Motor 2 Forward
   int m2_B = 13; //Motor 2 Reverse
   PiMotor motor1(m1_A, m1_B);
   PiMotor motor2(m2_A, m2_B);
   motor1.setDebug(true); //Turn on Debug message output (see console window!)
   motor2.setDebug(true); //Turn on Debug message output (see console window!)  
   motor1.runForMS(1,5, 4000); //Run for 4 seconds.
   motor2.runForMS(1,5, 4000); //Run for 4 seconds.
      // PID pid = PID(0.1, 100, -100, 0.1, 0.01, 0.5);
      //  double val = 20;
      //  for (int i = 0; i < 100; i++) 
      //    {
      //      double inc = pid.calculate(0, val);
      //      printf("val:% 7.3f inc:% 7.3f\n", val, inc);
      //      val += inc;
      //  }
   re_decoder dec1(7, 8, callback_left);
   re_decoder dec2(22, 23, callback_right);
   sleep(SAMPLETIME); // Pause 1 seconds
   dec1.re_cancel();
   dec2.re_cancel();
   gpioTerminate();     
}

