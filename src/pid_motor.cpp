#include<iostream>
#include<wiringPi.h>
#include<cstdlib>
using namespace std;


const int PWMpin = 1;   //只有wiringPi编号下的1脚（BCM标号下的18脚）支持
void setup();

int main()
{

    setup();
    int val = 0;
    int step = 2;
    while(true)
    {
        if(val>1024)
        {
            step = -step;    
            val = 1024;
        }
        else if(val<0)
        {
            step = -step;
            val = 0;
        }

        pwmWrite(PWMpin,val);
        val+=step;
        delay(10);
    }

    return 0;
}

void setup()
{
    if(-1==wiringPiSetup())
    {
        cerr<<"setup error\n";
        exit(-1);
    }
    pinMode(PWMpin,PWM_OUTPUT);
}