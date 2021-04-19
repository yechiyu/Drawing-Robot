// #ifndef TEST_H
// #define TEST_H
// #include <pigpio.h>
// #include <mutex>
// #include <iostream>
// using namespace std;

// class PiMotor {
//    private:
//       int fPin;
//       int rPin;
//       bool DEBUG = true;
   
//   public:
//       PiMotor(int, int);
//       void Run_left (int,bool);
//       void Run_right (int,bool);
   
//       int Stop_left();
//       int Stop_right();
//       void setDebug(bool); 
   
//    /*
//       This function establishes a rotary encoder on gpioA and gpioB.

//       When the encoder is turned the callback function is called.
//    */
// };


// #include <unistd.h>
// #include <stdio.h>
// #include <chrono>
// #include <functional>

// class control:public PiMotor,public re_decoder
// {
//   public:
//     void run_left(int speed_L,bool direction); // int , int , re_decoderCB_t ,int , int ,int ,bool
//     void run_right(int speed_R,bool direction); //int , int , re_decoderCB_t ,int , int ,int ,bool
//     void stop_left();
//     void stop_right();
//     control(int gpioA, int gpioB, re_decoderCB_t callback ,int forwardPin, int reversePin ):
//       re_decoder(gpioA, gpioB, callback),PiMotor(forwardPin,reversePin){}
//   private:
//     // int PL1=17;
//     // int PL2=27;
//     // int PR1=16;
//     // int PR2=19;
// };
// #endif