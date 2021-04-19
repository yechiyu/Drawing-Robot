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

// int m1_A = 20; //Motor 1 Forward
// int m1_B = 21; //Motor 1 Reverse
// int speed_left=20;
//     //bool direction_left=0;
// int m2_A = 6; //Motor 2 Forward
// int m2_B = 13; //Motor 2 Reverse
// int speed_right=20;
int PL1=16;
int PL2=19;
int PR1=17;
int PR2=27;
int pos[2]={0,0};
int callback_left(int way)
{
   //static int pos_left = 0;
   pos[0] += way;
   std::cout << "pos_left=" << pos[0] << std::endl;
   return pos[0];
}

int callback_right(int way)
{
   //static int pos_right = 0;
   pos[1] += way;
   //std::cout << "pos_right=" << pos[1] << std::endl;
   return pos[1];
}
class control:public PiMotor,public re_decoder
{
  public:
    void run_left(int speed_L,bool direction); // int , int , re_decoderCB_t ,int , int ,int ,bool
    void run_right(int speed_R,bool direction); //int , int , re_decoderCB_t ,int , int ,int ,bool
    void stop_left();
    void stop_right();
    //void stop_right();
    control(int gpioA, int gpioB, re_decoderCB_t callback ,int forwardPin, int reversePin ):
      re_decoder(gpioA, gpioB, callback),PiMotor(forwardPin,reversePin){}
  private:
    // int m1_A; //Motor 1 Forward
    // int m1_B; //Motor 1 Reverse
    // int speed_left;
    // int pina;
    // int pinb;
    // int (*re_decoderCB_t)(int);

};
void control::run_left(int speed_L,bool direction)   //int , int , re_decoderCB_t ,int , int ,int ,bool
{ 
   re_decoder::encoder_left(PL1,PL2,callback_left);
   PiMotor::Thread_run_left(speed_L,direction);
   
  
}
void control::run_right(int speed_R,bool direction)   //int , int , re_decoderCB_t ,int , int ,int ,bool
{
   PiMotor::Thread_run_right(speed_R,direction);
   re_decoder::encoder_right(PR1,PR2,callback_right);
}
void control::stop_left()
{
  re_decoder::re_cancel();
  PiMotor::Thread_stop_left();
  
}
void control::stop_right()
{
  re_decoder::re_cancel();
  PiMotor::Thread_stop_right();
  
}

// void run_creat(bool direction_right,bool direction_left)
//     {  
//     re_decoder dec1(7, 8, callback_left);
//     re_decoder dec2(9, 10, callback_right);
//     PiMotor motor1(m1_A, m1_B,speed_left,direction_left);
//     PiMotor motor2(m2_A, m2_B,speed_right,direction_right);
  
//     // motor1.setDebug(false); //Turn on Debug message output (see console window!)
//     // motor2.setDebug(false); //Turn on Debug message output (see console window!) 
//     // motor1.Thread_run_left();
//     // motor2.Thread_run_right();

//       // std::thread t1( std::bind( &PiMotor::Thread_run_left, &motor1 ) );
//       // std::thread t2( std::bind( &PiMotor::Thread_run_right, &motor2 ) );
//       // std::thread t3( std::bind( &re_decoder::encoder_left , &dec1,7, 8) );
//       // std::thread t4( std::bind( &re_decoder::encoder_right, &dec2,9, 10) );
//       // t1.join();
//       // t2.join();
//       // t3.join();
//       // t4.join();
//       }
// void run_stop(bool direction_right,bool direction_left)
// {
//       PiMotor motor3(m1_A, m1_B,speed_left,direction_left);
//       PiMotor motor4(m2_A, m2_B,speed_left,direction_right);
      
//       // int *p1=motor3.stop(); //Stop the motor 
//       // int *p2=motor4.stop(); //Stop the motor
       
//       //cout<<"11111"<<*p1<<" "<<*(p1+1)<<endl;
//       //cout<<"22222"<<*p2<<" "<<*(p2+1)<<endl;
//       // gpioTerminate(); 
//       // gpioSetAlertFunc(7, 0);
//       // gpioSetAlertFunc(8, 0);
//       // gpioSetAlertFunc(9, 0);
//       // gpioSetAlertFunc(10, 0);
//       gpioTerminate(); 

//     }
   
int main(int argc, char *argv[])

{  
   //if (gpioInitialise() < 0) return 1;
   int SAMPLETIME=5;// 3 sencond
   if (gpioInitialise() < 0)
    {
      fprintf(stderr, "igpio initialisation failed.\n\r");
     }
    else
    {
      fprintf(stderr, "igpio initialisation is okey.\n\r");
    }
    control left_motor(17,27,callback_left,20,21);
   //control right_motor(16,19,callback_right,6,13);
    
  left_motor.run_left(30,1);
    //right_motor.run_right(50,1);
    usleep(2000000);//5 seconds
   left_motor.stop_left();
  // right_motor.stop_right();
    usleep(1000000);//5 seconds
    left_motor.run_left(40,0);
  //   right_motor.run_right();
     usleep(2000000);//5 seconds
     left_motor.stop_left();
  //   right_motor.stop_right();
   
   // usleep(1000000);//5 seconds
     left_motor.run_left(50,1);
  //   right_motor.run_right();
     usleep(1000000);//5 seconds
     left_motor.stop_left();
  //   right_motor.stop_right();
    sleep(SAMPLETIME); // Pause 1 seconds
    gpioTerminate();     
    return 0;
}

