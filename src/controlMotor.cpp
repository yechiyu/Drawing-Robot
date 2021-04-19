#include "../include/controlMotor.h"

int pos[2]={0,0};
int callback_left(int way)
{
   pos[0] += way;
   return pos[0];
}

int callback_right(int way)
{
   pos[1] += way;
   return pos[1];
}

void control::run_left(int speed_L,bool direction)   //int , int , re_decoderCB_t ,int , int ,int ,bool
{ 
   re_decoder::encoder_left(17,27,callback_left);
   PiMotor::Run_left(speed_L,direction);
}

void control::run_right(int speed_R,bool direction)   //int , int , re_decoderCB_t ,int , int ,int ,bool
{
   PiMotor::Run_right(speed_R,direction);
   re_decoder::encoder_right(16,19,callback_right);
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
