#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include "../include/PiMotor.h"
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;
std::mutex x;

PiMotor::PiMotor(int forwardPin, int reversePin,int Speed,bool Direction ) {
    if (DEBUG) {
        printf("Creating motor object with pins %i and %i\n\r", forwardPin, reversePin);
    }
    
    fPin = forwardPin;
    rPin = reversePin;
    speed =Speed;
    direction=Direction;
}

void PiMotor::setDebug(bool debug) {
    DEBUG = debug;
    if (DEBUG) {
        printf("Debug messages enabled. Outputting all operations...\n\r");
    }
}

void PiMotor::stop() {
    //Initialise GPIO.
    if (gpioInitialise() < 0) {
        if (DEBUG) {
            fprintf(stderr, "PiGPIO initialisation failed.\n\r");
        }
      return;
   }
    gpioSetMode(fPin, PI_OUTPUT);
    gpioSetMode(rPin, PI_OUTPUT);
    gpioPWM(fPin, 0);
    gpioPWM(rPin, 0);
    
    if (DEBUG) {
        printf("Stopping motors on pin %i and pin %i.\n\r", rPin, fPin);
    }
   
   //Free resources & GPIO access
   //gpioTerminate();   
}

// void PiMotor::runForMS_left(int milliseconds) {
//     //Convert Milliseconds to Microseconds for usleep (unix)
//     unsigned int microseconds = (milliseconds * 1000.0);
//     if (DEBUG) {
//         printf("Running PiMotor::run for %i milliseconds.\n\r", milliseconds);
//     }
//     //Run
//     PiMotor::Thread_run_left();
//     //Wait
//     usleep(microseconds);
//     //Stop
//     PiMotor::Thread_run_left();
    
//     if (DEBUG) {
//         printf("Stopping PiMotor::run\n\r");
//     }
// }

// void PiMotor::runForMS_right(int milliseconds) {
//     //Convert Milliseconds to Microseconds for usleep (unix)
//     unsigned int microseconds = (milliseconds * 1000.0);
//     if (DEBUG) {
//         printf("Running PiMotor::run for %i milliseconds.\n\r", milliseconds);
//     }
//     //Run
//     PiMotor::Thread_run_right();
//     //Wait
//     usleep(microseconds);
//     //Stop
//     PiMotor::Thread_run_right();
    
//     if (DEBUG) {
//         printf("Stopping PiMotor::run\n\r");
//     }
// }

// void PiMotor::Thread_run_left () {
    
//     cout<<"enter Thread_run_left"<<endl;
//     x.lock();
//     cout<<"enter Thread_run_left........."<<endl;
//     if (gpioInitialise() < 0) {
//         if (DEBUG) {
//             fprintf(stderr, "PiGPIO initialisation failed in PiMotor::run.\n\r");
//         }
//       return;
//    }
//   int Direction;
//   if (direction == false) {
//       Direction = rPin;
//   } else if (direction == true) {
//       Direction = fPin;
//   } else {
//       if (DEBUG) {
//         fprintf(stderr, "Invalid Direction Value in PiMotor::run\n\r");
//       }
//       return;
    
//   }
  
//    //Set motor as output.
//     gpioInitialise();
//     gpioSetMode(26, PI_ALT0);
//     //gpioSetMode(12, PI_ALT0);
//     //gpioSetPullUpDown(26, PI_PUD_UP);
//     //gpioSetPullUpDown(12, PI_PUD_UP);
//     //gpioWrite(12, 1);// Sets a pull-up.
//     gpioWrite(26, 1);// Sets a pull-up.
//     gpioSetMode(Direction, PI_OUTPUT);
    
//     gpioPWM(Direction, speed);
//     if (1) {
//         if(Direction==rPin){
//         printf("Setting speed to %i on right_motor pin %i \n\r", speed, rPin);}
//         if(Direction==fPin){
//             printf("Setting speed to %i on right_motor pin %i \n\r", speed, fPin);}
//     }
   
   
//    //Free resources & GPIO access
//    gpioTerminate();
//    x.unlock();
// }

void PiMotor::Thread_run_right () {
    cout<<"enter Thread_run_left"<<endl;
    x.lock();
    cout<<"enter Thread_run_left................."<<endl;
    if (gpioInitialise() < 0) {
        if (DEBUG) {
            fprintf(stderr, "PiGPIO initialisation failed in PiMotor::run.\n\r");
        }
      return;
   }
   int Direction;
  if (direction == 0) {
     
      Direction = rPin;
  } else if (direction == 1) {
      Direction = fPin;
  } 
  else {
      if (DEBUG) {
        fprintf(stderr, "Invalid Direction Value in PiMotor::run\n\r");
      }
      return;
  }
  
   //Set motor as output.
    gpioInitialise();
    gpioSetMode(26, PI_ALT0);
    gpioSetMode(12, PI_ALT0);
    // gpioSetPullUpDown(26, PI_PUD_UP);
    // gpioSetPullUpDown(12, PI_PUD_UP);
    gpioWrite(12, 1);// Sets a pull-up.
    gpioWrite(26, 1);// Sets a pull-up.
    gpioSetMode(Direction, PI_OUTPUT);
    
    gpioPWM(Direction, speed);
    if (DEBUG) {
        if(Direction==rPin){
        printf("Setting speed to %i on right_motor pin %i \n\r", speed, rPin);}
        if(Direction==fPin){
            printf("Setting speed to %i on right_motor pin %i \n\r", speed, fPin);}
    }
   
   //Free resources & GPIO access
   //gpioTerminate();
   x.unlock();
}

void PiMotor::_pulse(int gpio, int level, uint32_t tick)
{
   if (gpio == mygpioA) levA = level; else levB = level;

   if (gpio != lastGpio) /* debounce */
   {
      lastGpio = gpio;

      if ((gpio == mygpioA) && (level == 1))
      {
         if (levB) (mycallback)(1);
      }
      else if ((gpio == mygpioB) && (level == 1))
      {
         if (levA) (mycallback)(-1);
      }
   }
}

void PiMotor::_pulseEx(int gpio, int level, uint32_t tick, void *user)
{
   /*
      Need a static callback to link with C.
   */

   PiMotor *mySelf = (PiMotor *) user;

   mySelf->_pulse(gpio, level, tick); /* Call the instance callback. */
}

void PiMotor::re_decoder(int gpioA, int gpioB, re_decoderCB_t callback)
{
   mygpioA = gpioA;
   mygpioB = gpioB;

   mycallback = callback;

   levA=0;
   levB=0;

   lastGpio = -1;

   gpioSetMode(gpioA, PI_INPUT);
   gpioSetMode(gpioB, PI_INPUT);

   /* pull up is needed as encoder common is grounded */

   gpioSetPullUpDown(gpioA, PI_PUD_UP);
   gpioSetPullUpDown(gpioB, PI_PUD_UP);

   /* monitor encoder level changes */

   gpioSetAlertFuncEx(gpioA, _pulseEx, this);
   gpioSetAlertFuncEx(gpioB, _pulseEx, this);
}

void PiMotor::re_cancel(void)
{
   gpioSetAlertFuncEx(mygpioA, 0, this);
   gpioSetAlertFuncEx(mygpioB, 0, this);
}

