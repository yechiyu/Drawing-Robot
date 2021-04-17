#include <cstdlib>
#include <stdio.h>
#include "../include/PiMotor.h"
#include "pigpio.h"
#include <unistd.h>
// #include "./include/MotorThread.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;


int main(int argc, char *argv[]){
    //Create a new instance for our Motor.
    
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
    motor1.setDebug(1); //Turn on Debug message output (see console window!)
    motor2.setDebug(1); //Turn on Debug message output (see console window!) 
    std::thread t2( std::bind( &PiMotor::Thread_run_right, &motor1 ) );
    std::thread t1( std::bind( &PiMotor::Thread_run_right, &motor2 ) );
    t2.join();
    t1.join();
     
    // motor2.runForMS_right(0,50,4000); //Set PWM value for direction (0 = reverse, 1 = forwards)
    // motor1.runForMS_left(1,50,4000);//Set PWM value for direction (0 = reverse, 1 = forwards)
   
    
    usleep(5000000);//5 seconds
    motor1.stop(); //Stop the motor 
    motor2.stop(); //Stop the motor  
    gpioTerminate();
    return 0;
}
 