#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include "../include/PiMotor.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <functional>
using namespace std;
std::mutex x;
extern int pos[2];

PiMotor::PiMotor(int forwardPin, int reversePin)
{
    if (DEBUG) {
        printf("Creating motor object with pins %i and %i\n\r", forwardPin, reversePin);
    }
    
    fPin = forwardPin;
    rPin = reversePin;
    // speed =Speed;
    // direction=Direction;
    //function=f;
}
 
void PiMotor::setDebug(bool debug) {
    DEBUG = debug;
    if (DEBUG) {
        printf("Debug messages enabled. Outputting all operations...\n\r");
    }
}

int PiMotor::Thread_stop_left() {
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
    int Posion=0;
    Posion=pos[0];
    pos[0]=0;
    if (DEBUG) {
        printf("Stopping motors on pin %i and pin %i.\n\r", rPin, fPin);
    }
    return Posion;
   
   //Free resources & GPIO access
   gpioTerminate();   
}

int PiMotor::Thread_stop_right() {
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
    int Posion=0;
    Posion=pos[1];
    pos[1]=0;
    if (DEBUG) {
        printf("Stopping motors on pin %i and pin %i.\n\r", rPin, fPin);
    }
    return Posion;
   
   //Free resources & GPIO access
   gpioTerminate();   
}

void PiMotor::Thread_run_right (int Speed_R,bool Direction) {
    cout<<"enter Thread_run_right"<<endl;
    //x.lock();
    if (gpioInitialise() < 0) {
    if (DEBUG) {
        fprintf(stderr, "PiGPIO initialisation failed in PiMotor::run.\n\r");
    }
    return;
   }
    
  cout<<"before direction right is  "<<Direction<<endl;
  int D=0;
  if (Direction == 0) {
     
      D = rPin;
  } else if (Direction== 1) {
      D = fPin;
  } 
  else {
      if (DEBUG) {
        fprintf(stderr, "Invalid Direction Value in PiMotor::run\n\r");
      }
      return;
  }
  cout<<"after direction right is  "<<D<<endl;
    gpioInitialise();
    cout<<"set pin12 high"<<endl;
    gpioSetMode(12, PI_ALT0);
    gpioWrite(12, 1);// Sets a pull-up.
   //gpioSetMode(26, PI_ALT0);

   //gpioWrite(26, 1);// Sets a pull-up.
    //gpioSetPullUpDown(26, PI_PUD_UP);
    //gpioSetPullUpDown(12, PI_PUD_UP);
   // gpioInitialise();
     gpioSetMode(D, PI_OUTPUT);
    //gpioSetPWMrange(D, 1000);
    gpioPWM(D,Speed_R);

   
  
   //Set motor as output.
    //gpioInitialise();
    //gpioSetMode(26, PI_ALT0);
    
   
    
    
    //pioWrite(26, 1);// Sets a pull-up.
    
      if (DEBUG) {
        if(D==rPin){
        printf("Setting speed to %i on motor pin %i \n\r", Speed_R, rPin);}
        if(D==fPin){
            printf("Setting speed to %i on motor pin %i \n\r", Speed_R, fPin);}
    }
    
   
  
   
   //Free resources & GPIO access
   gpioTerminate();
   //x.unlock();
}

void PiMotor::Thread_run_left (int Speed_L,bool Direction) {
    cout<<"enter Thread_run_left"<<endl;
    //x.lock();
   if (gpioInitialise() < 0) {
        if (DEBUG) {
            fprintf(stderr, "PiGPIO initialisation failed in PiMotor::run.\n\r");
        }
      return;
   }
    cout<<"before direction left is  "<<Direction<<endl;
   int D=0;
  if (Direction == 0) {
     
      D= rPin;
  } else if (Direction == 1) {
     D= fPin;
  } 
  else {
      if (DEBUG) {
        fprintf(stderr, "Invalid Direction Value in PiMotor::run\n\r");
      }
      return;
  }
   cout<<"after direction left is  "<<D<<endl;
    gpioInitialise();
    cout<<"set pin26 high"<<endl;
    gpioSetMode(26, PI_ALT0);
    //gpioSetMode(12, PI_ALT0);
    gpioWrite(26, 1);// Sets a pull-up.
    //gpioWrite(12, 1);// Sets a pull-up.
    // gpioSetPullUpDown(26, PI_PUD_UP);
    // gpioSetPullUpDown(12, PI_PUD_UP);
    //gpioInitialise();
    gpioSetMode(D, PI_OUTPUT);
    //gpioSetPWMrange(D, 1000);
    gpioPWM(D, Speed_L);

   
  
   //Set motor as output.
    //gpioInitialise();
    
    
    //gpioSetMode(12, PI_ALT0);
   
    //gpioWrite(12, 1);// Sets a pull-up.
    
    if (DEBUG) {
        if(D==rPin){
        printf("Setting speed to %i on motor pin %i \n\r", Speed_L, rPin);}
        if(D==fPin){
            printf("Setting speed to %i on motor pin %i \n\r", Speed_L, fPin);}
    }
    
    
   
   //Free resources & GPIO access
   //gpioTerminate();
   //x.unlock();
}

void re_decoder::_pulse(int gpio, int level, uint32_t tick)
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

void re_decoder::_pulseEx(int gpio, int level, uint32_t tick, void *user)
{
   /*
      Need a static callback to link with C.
   */

   re_decoder *mySelf = (re_decoder *) user;

   mySelf->_pulse(gpio, level, tick); /* Call the instance callback. */
}
void re_decoder::encoder_left(int gpioA, int gpioB, re_decoderCB_t callback)
{
   mygpioA = gpioA;
   
   mygpioB = gpioB;

   mycallback = callback;

   levA=0;
   levB=0;

   lastGpio = -1;
    if (gpioInitialise() < 0)
    {
      fprintf(stderr, "igpio initialisation failed.\n\r");
     }
    else
    {
      fprintf(stderr, "igpio initialisation is okey.\n\r");
    }
   gpioSetMode(gpioA, PI_INPUT);
   gpioSetMode(gpioB, PI_INPUT);

   /* pull up is needed as encoder common is grounded */

   gpioSetPullUpDown(gpioA, PI_PUD_UP);
   gpioSetPullUpDown(gpioB, PI_PUD_UP);

   /* monitor encoder level changes */

   gpioSetAlertFuncEx(gpioA, _pulseEx, this);
   gpioSetAlertFuncEx(gpioB, _pulseEx, this);
   }

void re_decoder::encoder_right(int gpioA, int gpioB, re_decoderCB_t callback)
{  
   
   mygpioA = gpioA;
   
   mygpioB = gpioB;

   mycallback = callback;

   levA=0;
   levB=0;

   lastGpio = -1;
    if (gpioInitialise() < 0)
    {
      fprintf(stderr, "igpio initialisation failed.\n\r");
     }
    else
    {
      fprintf(stderr, "igpio initialisation is okey.\n\r");
    }
   gpioSetMode(gpioA, PI_INPUT);
   gpioSetMode(gpioB, PI_INPUT);

   /* pull up is needed as encoder common is grounded */

   gpioSetPullUpDown(gpioA, PI_PUD_UP);
   gpioSetPullUpDown(gpioB, PI_PUD_UP);

   /* monitor encoder level changes */

   gpioSetAlertFuncEx(gpioA, _pulseEx, this);
   gpioSetAlertFuncEx(gpioB, _pulseEx, this);
   }
re_decoder::re_decoder(int gpioA, int gpioB, re_decoderCB_t callback)
{
   mygpioA = gpioA;
   
   mygpioB = gpioB;

   mycallback = callback;

   levA=0;
   levB=0;

   lastGpio = -1;
//    gpioSetMode(gpioA, PI_INPUT);
//    gpioSetMode(gpioB, PI_INPUT);

//    /* pull up is needed as encoder common is grounded */

//    gpioSetPullUpDown(gpioA, PI_PUD_UP);
//    gpioSetPullUpDown(gpioB, PI_PUD_UP);

//    /* monitor encoder level changes */

//    gpioSetAlertFuncEx(gpioA, _pulseEx, this);
//    gpioSetAlertFuncEx(gpioB, _pulseEx, this);

   
}

void re_decoder::re_cancel(void)
{   if (gpioInitialise() < 0) 
//      {
//          cout<<"PiGPIO initialisation failed in PiMotor::run.\n\r"<<endl;
//      }
   gpioSetAlertFuncEx(mygpioA, 0, this);
   gpioSetAlertFuncEx(mygpioB, 0, this);
}