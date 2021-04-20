#include "../include/PiMotor.h"

extern int pos[2];

PiMotor::PiMotor(int forwardPin, int reversePin)
{
    if (DEBUG) {
        printf("Creating motor object with pins %i and %i\n\r", forwardPin, reversePin);
    }    
    fPin = forwardPin;
    rPin = reversePin;
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
    Posion=pos[0];
    pos[0]=0;
    if (DEBUG) {
        printf("Stopping motors on pin %i and pin %i.\n\r", rPin, fPin);
    }
    return Posion;

   gpioTerminate();   
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
    gpioTerminate();   
}

void PiMotor::Run_right (int Speed_R,bool Direction) {
    //x.lock();
    if (gpioInitialise() < 0) {
    if (DEBUG) {
        fprintf(stderr, "PiGPIO initialisation failed in PiMotor::run.\n\r");
    }
    return;
   }

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
    // cout<<"after direction right is  "<<D<<endl;
    gpioInitialise();
    // cout<<"set pin12 high"<<endl;
    gpioSetMode(12, PI_ALT0);
    gpioWrite(12, 1);// Sets a pull-up.
    gpioSetMode(D, PI_OUTPUT);
    gpioPWM(D,Speed_R);
    
    if (DEBUG) {
        if(D==rPin){
        printf("Setting speed to %i on motor pin %i \n\r", Speed_R, rPin);}
        if(D==fPin){
            printf("Setting speed to %i on motor pin %i \n\r", Speed_R, fPin);}
    }
}

void PiMotor::Run_left (int Speed_L,bool Direction) {
    // cout<<"enter Thread_run_left"<<endl;
    //x.lock();
    if (gpioInitialise() < 0) {
            if (DEBUG) {
                fprintf(stderr, "PiGPIO initialisation failed in PiMotor::run.\n\r");
            }
        return;
    }
    // cout<<"before direction left is  "<<Direction<<endl;
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
    // cout<<"after direction left is  "<<D<<endl;
    gpioInitialise();
    // cout<<"set pin26 high"<<endl;
    gpioSetMode(26, PI_ALT0);
    gpioWrite(26, 1);// Sets a pull-up.
    gpioSetMode(D, PI_OUTPUT);
    gpioPWM(D, Speed_L);

    if (DEBUG) {
        if(D==rPin){
        printf("Setting speed to %i on motor pin %i \n\r", Speed_L, rPin);}
        if(D==fPin){
            printf("Setting speed to %i on motor pin %i \n\r", Speed_L, fPin);}
    }
}

void Pi_servo(int Fre)//1500 undraw 2500draw
{
    if(gpioInitialise()<0)
     {
        cout<<"pigpio intialisation failed."<<endl;
     }
    else
     {
         cout<<"pigpio initialised okay"<<endl;
     }
    int servo_pin=18;
    gpioSetMode(servo_pin,PI_OUTPUT);
    gpioSetPWMfrequency(servo_pin, 400);
    gpioServo(servo_pin,Fre);
}