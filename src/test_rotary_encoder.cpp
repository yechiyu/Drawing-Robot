#include <iostream>
#include <pigpio.h>
#include <unistd.h>
//#include "rotary_encoder.hpp"
#include "../include/PiMotor.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;
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
   std::cout << "pos_right=" << pos_right << std::endl;
   return pos_right;
}

   
int main(int argc, char *argv[])
{
   if (gpioInitialise() < 0) return 1;
   int SAMPLETIME=100;// 3 sencond
   if (gpioInitialise() < 0)
    {
      fprintf(stderr, "igpio initialisation failed.\n\r");
     }
    else
    {
      fprintf(stderr, "igpio initialisation is okey.\n\r");
    }
    
    
    int m1_A = 20; //Motor 1 Forward
    int m1_B = 21; //Motor 1 Reverse
    int speed_left=60;
    bool direction_left=1;
    int m2_A = 6; //Motor 2 Forward
    int m2_B = 13; //Motor 2 Reverse
    int speed_right=30;
    bool direction_right=1;
    // gpioSetMode(26, PI_ALT0);
    // gpioSetMode(12, PI_ALT0);
    // gpioSetPullUpDown(26, PI_PUD_UP);
    // gpioSetPullUpDown(12, PI_PUD_UP);
    // gpioWrite(12, 1);// Sets a pull-up.
    // gpioWrite(26, 1);// Sets a pull-up.
   PiMotor motor1(m1_A, m1_B,speed_left,direction_left);
   PiMotor motor2(m2_A, m2_B,speed_left,direction_right);
   // re_decoder dec1(7, 8, callback_left);
   // re_decoder dec2(22, 23, callback_right);
    motor1.setDebug(false); //Turn on Debug message output (see console window!)
    motor2.setDebug(false); //Turn on Debug message output (see console window!) 
    std::thread t2( std::bind( &PiMotor::Thread_run_right, &motor1 ) );
    std::thread t1( std::bind( &PiMotor::Thread_run_right, &motor2 ) );
    std::thread t3( std::bind( &PiMotor::re_decoder, &motor1,9, 10, callback_left ) );
    std::thread t4( std::bind( &PiMotor::re_decoder, &motor2,7, 8, callback_right) );
    t2.join();
    t1.join();
    t3.join();
    t4.join();
    // motor2.runForMS_right(0,50,4000); //Set PWM value for direction (0 = reverse, 1 = forwards)
    // motor1.runForMS_left(1,50,4000);//Set PWM value for direction (0 = reverse, 1 = forwards)
   
    
    usleep(5000000);//5 seconds
    motor1.stop(); //Stop the motor 
    motor2.stop(); //Stop the motor 
      // PID pid = PID(0.1, 100, -100, 0.1, 0.01, 0.5);
      //  double val = 20;
      //  for (int i = 0; i < 100; i++) 
      //    {
      //      double inc = pid.calculate(0, val);
      //      printf("val:% 7.3f inc:% 7.3f\n", val, inc);
      //      val += inc;
      //  }
   
   sleep(SAMPLETIME); // Pause 1 seconds
   motor1.re_cancel();
   motor2.re_cancel();
   gpioTerminate();     
}

