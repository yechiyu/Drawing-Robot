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

// int callback_left(int way)
// {
//    static int pos_left = 0;
//    pos_left += way;
//    std::cout << "pos_left=" << pos_left << std::endl;
//    return pos_left;
// }

// int callback_right(int way)
// {
//    static int pos_right = 0;
//    pos_right += way;
//    std::cout << "pos_right=" << pos_right << std::endl;
//    return pos_right;
// }
int m1_A = 20; //Motor 1 Forward
int m1_B = 21; //Motor 1 Reverse
int speed_left=50;
    //bool direction_left=0;
int m2_A = 6; //Motor 2 Forward
int m2_B = 13; //Motor 2 Reverse
int speed_right=30;
void run_creat(bool direction_right,bool direction_left)
    {
      PiMotor motor1(m1_A, m1_B,speed_left,direction_left);
      PiMotor motor2(m2_A, m2_B,speed_left,direction_right);
      // re_decoder dec1(7, 8, callback_left);
      // re_decoder dec2(22, 23, callback_right);
      motor1.setDebug(false); //Turn on Debug message output (see console window!)
      motor2.setDebug(false); //Turn on Debug message output (see console window!) 
      std::thread t1( std::bind( &PiMotor::Thread_run_right, &motor1 ) );
      std::thread t2( std::bind( &PiMotor::Thread_run_right, &motor2 ) );
      std::thread t3( std::bind( &PiMotor::re_decoder, &motor1,9, 10, callback_left) );
      std::thread t4( std::bind( &PiMotor::re_decoder, &motor2,7, 8, callback_right) );
      t1.join();
      t2.join();
      t3.join();
      t4.join();
      }
void run_stop(bool direction_right,bool direction_left)
{
      PiMotor motor3(m1_A, m1_B,speed_left,direction_left);
      PiMotor motor4(m2_A, m2_B,speed_left,direction_right);
      
      int *p1=motor3.stop(); //Stop the motor 
      int *p2=motor4.stop(); //Stop the motor
      cout<<"11111"<<*p1<<" "<<*(p1+1)<<endl;
      cout<<"22222"<<*p2<<" "<<*(p2+1)<<endl;

    }
   
int main(int argc, char *argv[])
{
   if (gpioInitialise() < 0) return 1;
   int SAMPLETIME=5;// 3 sencond
  //  if (gpioInitialise() < 0)
  //   {
  //     fprintf(stderr, "igpio initialisation failed.\n\r");
  //    }
  //   else
  //   {
  //     fprintf(stderr, "igpio initialisation is okey.\n\r");
  //   }
    
    
    run_creat(1,1);
    usleep(3000000);//5 seconds
    run_stop(1,1);
    usleep(3000000);//5 seconds
    run_creat(0,0);
    usleep(2000000);//5 seconds
    run_stop(1,1);
    usleep(3000000);//5 seconds
    run_creat(0,0);
    usleep(1000000);//5 seconds
    run_stop(1,1);
    sleep(SAMPLETIME); // Pause 1 seconds
    gpioTerminate();     
}

