#ifndef CONTROLMOTOR_H
#define CONTROLMOTOR_H

#include "../include/PiMotor.h"
#include "../include/reDecoder.h"

#include <unistd.h>
#include <stdio.h>
#include <chrono>
#include <functional>

class control:public PiMotor,public re_decoder
{
  public:
    void run_left(int speed_L,bool direction); // int , int , re_decoderCB_t ,int , int ,int ,bool
    void run_right(int speed_R,bool direction); //int , int , re_decoderCB_t ,int , int ,int ,bool
    void stop_left();
    void stop_right();
    control(int gpioA, int gpioB, re_decoderCB_t callback ,int forwardPin, int reversePin ):
      re_decoder(gpioA, gpioB, callback),PiMotor(forwardPin,reversePin){}
  private:
    // int PL1=17;
    // int PL2=27;
    // int PR1=16;
    // int PR2=19;
};
#endif