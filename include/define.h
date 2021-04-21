#ifndef DEFINE_H
#define DEFINE_H

#include "../include/calPosition.h"
#include "../include/movetoTarget.h"
#include "../include/processImages.h"
#include "../include/controlMotor.h"
#include "../include/pixtoMeter.h"
#include <thread>
#include <stdlib.h>

std::mutex x;
calPosition cp;
movetoTarget mt;

extern int pos[2];
int targetCounts1, targetCounts2;
double *result;
control left_motor(17,27,callback_left,20,21);
control right_motor(16,19,callback_right,6,13);


void MotorL_Tread()
    { 
      // std::lock_guard<std::mutex> locker(x);
      // cout<<"b= "<<targetCounts1<<endl;
      while(abs(pos[0]) < abs(targetCounts1))
      {
        // cout<<"l= "<<pos[0]<<endl;
        usleep(10000);//5 seconds
      };
      left_motor.stop_left();
      Pi_servo(1950);
      usleep(100000);
      Pi_servo(1500);
      usleep(100000);
    }

void MotorR_Tread()
   {  
      // std::lock_guard<std::mutex> locker(x);
      while(abs(pos[1]) < abs(targetCounts2))
      {
        // cout<<"r= "<<pos[1]<<endl;
        usleep(10000);//5 seconds
      };
      right_motor.stop_right();
      Pi_servo(1950);
      usleep(100000);
      Pi_servo(1500);
      usleep(100000);
   }




        // string url = "../img/1.jpg";


#endif