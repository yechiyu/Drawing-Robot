#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include "rotary_encoder.hpp"
#include "pid.h"

/*
REQUIRES

A rotary encoder contacts A and B connected to separate gpios and
the common contact connected to Pi ground.

TO BUILD

g++ -o rot_enc_cpp test_rotary_encoder.cpp rotary_encoder.cpp -lpigpio -lrt

TO RUN

sudo ./rot_enc_cpp

*/

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
   std::cout << "pos_left=" << pos_right << std::endl;
   return pos_right;
}

int main(int argc, char *argv[])
{
   if (gpioInitialise() < 0) return 1;

   re_decoder dec1(7, 8, callback_left);
   re_decoder dec2(17, 18, callback_right);
   PID pid = PID(0.1, 100, -100, 0.1, 0.01, 0.5);

    double val = 20;
    for (int i = 0; i < 100; i++) {
        double inc = pid.calculate(0, val);
        printf("val:% 7.3f inc:% 7.3f\n", val, inc);
        val += inc;
    }
   sleep(3000);

   dec1.re_cancel();
   dec2.re_cancel();
   gpioTerminate();
}

