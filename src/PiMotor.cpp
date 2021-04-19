#include "../include/PiMotor.h"

extern int pos[2];
PiMotor::PiMotor(int forwardPin, int reversePin,int Speed,bool Direction)
{
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

int PiMotor::Stop_left() {
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
    Posion = pos[0];
    pos[0] = 0;
    if (DEBUG) {
        printf("Stopping motors on pin %i and pin %i.\n\r", rPin, fPin);
    }
    return Posion;
   
   //Free resources & GPIO access
   //gpioTerminate();   
}

int PiMotor::Stop_right() {
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
   //gpioTerminate();   
}

void PiMotor::Run_right () {
    // cout<<"enter Thread_run_left"<<endl;
    //x.lock();
    if (gpioInitialise() < 0) {
    if (DEBUG) {
        fprintf(stderr, "PiGPIO initialisation failed in PiMotor::run.\n\r");
    }
    return;
    }
    gpioSetMode(12, PI_ALT0);
    gpioWrite(12, 1);// Sets a pull-up.
    int D=0;
    if (direction == 0) {
        
        D = rPin;
    } else if (direction== 1) {
        D = fPin;
    } 
    else {
        if (DEBUG) {
            fprintf(stderr, "Invalid Direction Value in PiMotor::run\n\r");
        }
        return;
    }
    gpioInitialise();
    gpioSetMode(D, PI_OUTPUT);
    gpioPWM(D,speed);
    
    if (DEBUG) {
        if(D==rPin){
        printf("Setting speed to %i on motor pin %i \n\r", speed, rPin);}
        if(D==fPin){
            printf("Setting speed to %i on motor pin %i \n\r", speed, fPin);}
    }
}

void PiMotor::Run_left () {
    // cout<<"enter Thread_run_left"<<endl;
    //x.lock();
   if (gpioInitialise() < 0) {
        if (DEBUG) {
            fprintf(stderr, "PiGPIO initialisation failed in PiMotor::run.\n\r");
        }
      return;
   }
   int D=0;
  if (direction == 0) {
     
      D= rPin;
  } else if (direction == 1) {
     D= fPin;
  } 
  else {
      if (DEBUG) {
        fprintf(stderr, "Invalid Direction Value in PiMotor::run\n\r");
      }
      return;
  }
    gpioInitialise();
    gpioSetMode(26, PI_ALT0);
    gpioWrite(26, 1);// Sets a pull-up.
    gpioSetMode(D, PI_OUTPUT);
    gpioPWM(D, speed);
    
    if (DEBUG) {
        if(D==rPin){
        printf("Setting speed to %i on motor pin %i \n\r", speed, rPin);}
        if(D==fPin){
            printf("Setting speed to %i on motor pin %i \n\r", speed, fPin);}
    }  
   //Free resources & GPIO access
   //gpioTerminate();
   //x.unlock();
}
