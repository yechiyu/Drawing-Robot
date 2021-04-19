#include "../include/calPosition.h"
#include "../include/movetoTarget.h"
#include "../include/processImages.h"
#include "../include/controlMotor.h"
#include <iostream>
#include <thread>
std::mutex x;
calPosition cp;
movetoTarget mt;
processImages pi;

double *result;
void MotorL_Tread(int a,int b)
    { 
      std::lock_guard<std::mutex> locker(x);
      int i = 0;
      while(abs(a) < abs(b))
      {
      usleep(10000);//5 seconds
      i++;
      }
    }
void MotorR_Tread(int a,int b)
   {  
      std::lock_guard<std::mutex> locker(x);
      int i = 0;
      while(abs(a)<=b)
    {
      usleep(10000);//5 seconds
      cout << i << ":" << a<< endl;
      i++;
    }
  }
    
int main() 
{  
    
    double L1 = 0.425; //the distances between the motors and the pulley（left）
    double L2 = 0.425; //the distances between the motors and the pulley（right）
    
    int speeds = 50;
    bool dir;
    // string url = "../img/3.jpg";

    extern int pos[2];
    int counts1 = pos[0]; //the encoders give motor positions in counts
    int counts2 = pos[1];

    double targetX = 0.4; // target x
    double targetY = 0.2;  // target y

    double currrentX, currrentY;
    int targetCounts1, targetCounts2;

    // intial position
    result = cp.initialPosition(L1,L2);

    cout << "Initial X: " << result[0] << endl;
    cout << "Initial Y: " << result[1] << endl;

    // current position
    result = cp.currentPosition(counts1,counts2);

    currrentX = result[0];
    currrentY = result[1];

    cout << "Current X: " << result[0] << endl;
    cout << "Current Y: " << result[1] << endl;

    // obtain the x,y
    // ci.process(url);
    // int i = ci.i;
    // for(int j=0;j<i;j++)
    // {
    //     targetX = ci.pointImg[j][0];
    //     targetY = ci.pointImg[j][1];

    //     result = mt.calCounts(targetX,targetY,result[0], result[1]);

    //     targetCounts1 = result[0];
    //     targetCounts2 = result[1];


    //     // cout << "counts1:" << counts1 << endl;
    //     // cout << "counts2:" << counts2 << endl;
    // } 

    // x,y to counts
    result = mt.calCounts(targetX,targetY,currrentX,currrentY);
    
    targetCounts1 = result[0];
    targetCounts2 = result[1];

    cout << "targetCounts1:" << targetCounts1 << endl;
    cout << "targetCounts2:" << targetCounts2 << endl;
     
    // control the robot

    control left_motor(17,27,callback_left,20,21);
    control right_motor(16,19,callback_right,6,13);
    
    if(targetCounts1 > 0){
        dir = 1;
    }else{
        dir = 0;
    }
     if (gpioInitialise() < 0)
    {
      fprintf(stderr, "igpio initialisation failed.\n\r");
     }
    else
    {
      fprintf(stderr, "igpio initialisation is okey.\n\r");
    }
    left_motor.run_left(speeds,dir);
    // int i = 0;
    // while(abs(pos[0]) < abs(targetCounts1)){
    //   usleep(10000);//5 seconds
    //   i++;
    // }
    std::thread t1(&MotorL_Tread,pos[0],targetCounts1);
    t1.join();
    left_motor.stop_left();

    right_motor.run_right(50,1);
    std::thread t2(&MotorR_Tread,pos[1],targetCounts2);
    t2.join();
    // int i = 0;
    // while(abs(pos[1])<=targetCounts2){
    //   usleep(10000);//5 seconds
    //   cout << i << ":" << pos[1]<< endl;
    //   i++;
    // }
    left_motor.stop_left();

    gpioTerminate(); 
}
