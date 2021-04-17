#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include "../include/PiMotor.h"
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;
std::mutex x;
static int pos[2]={0,0};
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
   std::cout << "pos_right=" << pos[1] << std::endl;
   return pos[1];
}

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

int * PiMotor::stop() {
    //Initialise GPIO.
    if (gpioInitialise() < 0) {
        if (DEBUG) {
            fprintf(stderr, "PiGPIO initialisation failed.\n\r");
        }
   }
    gpioSetMode(fPin, PI_OUTPUT);
    gpioSetMode(rPin, PI_OUTPUT);
    gpioPWM(fPin, 0);
    gpioPWM(rPin, 0);
    static int Posion[2]={0,0};
    Posion[0]=pos[0];
    Posion[1]=pos[1];
    pos[0]=0;
    pos[1]=0;
    if (DEBUG) {
        printf("Stopping motors on pin %i and pin %i.\n\r", rPin, fPin);
    }
    return Posion;
   
   //Free resources & GPIO access
   //gpioTerminate();   
}



void PiMotor::Thread_run_right () {
    cout<<"enter Thread_run_left"<<endl;
    //x.lock();
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
        printf("Setting speed to %i on motor pin %i \n\r", speed, rPin);}
        if(Direction==fPin){
            printf("Setting speed to %i on motor pin %i \n\r", speed, fPin);}
    }
   
   //Free resources & GPIO access
   //gpioTerminate();
   //x.unlock();
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

