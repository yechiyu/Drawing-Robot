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
    void run_left(); // int , int , re_decoderCB_t ,int , int ,int ,bool
    void run_right(); //int , int , re_decoderCB_t ,int , int ,int ,bool
    void stop_left();
    void stop_right();
    //void stop_right();
    control(int gpioA, int gpioB, re_decoderCB_t callback ,int forwardPin, int reversePin,int Speed,bool Direction ):
      re_decoder(gpioA, gpioB, callback),PiMotor(forwardPin,reversePin,Speed,Direction){}
  private:
    int PL1=26;
    int PL2=19;
    int PR1=7;
    int PR2=8;
};
#endif