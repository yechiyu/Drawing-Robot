#include "../include/controlMotor.h"

int pos[2]={0,0};
int callback_left(int way)
{
   //static int pos_left = 0;
   pos[0] += way;
   // std::cout << "pos_left=" << pos[0] << std::endl;
   return pos[0];
}

int callback_right(int way)
{
   //static int pos_right = 0;
   pos[1] += way;
   // std::cout << "pos_right=" << pos[1] << std::endl;
   return pos[1];
}

void control::run_left()   //int , int , re_decoderCB_t ,int , int ,int ,bool
{ 
   re_decoder::encoder_left(PL1,PL2,callback_left);
   PiMotor::Run_left();
}

void control::run_right()   //int , int , re_decoderCB_t ,int , int ,int ,bool
{
   PiMotor::Run_right();
   re_decoder::encoder_right(PR1,PR2,callback_right);
}

void control::stop_left()
{
  re_decoder::re_cancel();
  PiMotor::Stop_left();
}

void control::stop_right()
{
  re_decoder::re_cancel();
  PiMotor::Stop_right();
}
