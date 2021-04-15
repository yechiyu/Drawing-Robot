#include <cstdlib>
#include <stdio.h>
#include "../include/PiMotor.h"
#include "pigpio.h"
#include <unistd.h>
using namespace std;



int main(int argc, char *argv[]){
    //Create a new instance for our Motor.
    gpioInitialise();
    int m1_A = 6; //Motor 1 Forward
    int m1_B = 13; //Motor 1 Reverse
    gpioWrite(26, 1);// Sets a pull-up.
    gpioWrite(12, 1);// Sets a pull-up.
    PiMotor motor1(m1_A, m1_B);
    
    motor1.setDebug(true); //Turn on Debug message output (see console window!)
    motor1.run(0, 100); //Set PWM value for direction (0 = reverse, 1 = forwards)
    sleep(5);//3000 seconds
    motor1.stop(); //Stop the motor  
    motor1.runForMS(1, 100, 4000); //Run for 4 seconds.
    gpioTerminate();
    return 0;
}
 