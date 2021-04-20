#include "../include/calPosition.h"
#include "../include/movetoTarget.h"
#include "../include/processImages.h"
#include "../include/controlMotor.h"
#include "../include/dataTest.h"
#include <iostream>
#include <thread>
std::mutex x;
calPosition cp;
movetoTarget mt;
processImages pi;

extern int pos[2];
int targetCounts1, targetCounts2;
double *result;
control left_motor(17,27,callback_left,20,21);
control right_motor(16,19,callback_right,6,13);


void MotorL_Tread()
    { 
      // std::lock_guard<std::mutex> locker(x);
      // cout<<"b= "<<targetCounts1<<endl;
      while(abs(pos[0]) < abs(targetCounts1))
      {
        // cout<<"l= "<<pos[0]<<endl;
        usleep(10000);//5 seconds
      };
      left_motor.stop_left();
    }

void MotorR_Tread()
   {  
      // std::lock_guard<std::mutex> locker(x);
      while(abs(pos[1]) < abs(targetCounts2))
      {
        // cout<<"r= "<<pos[1]<<endl;
        usleep(10000);//5 seconds
      };
      right_motor.stop_right();
  }
    
int main() 
{  
    
    double L1 = 0.425; //the distances between the motors and the pulley（left）
    double L2 = 0.425; //the distances between the motors and the pulley（right）
    
    int speeds = 50;
    bool dir1,dir2;
    // string url = "../img/3.jpg";

    int counts1 = 0; //the encoders give motor positions in counts
    int counts2 = 0;

    double targetX; // target x
    double targetY;  // target y

    double currrentX, currrentY;

    // intial position
    result = cp.initialPosition(L1,L2);

    // cout << "Initial X: " << result[0] << endl;
    // cout << "Initial Y: " << result[1] << endl;

    // drawing
    for(int i=0;i<9;i++){
      targetX = dataGroup[i][0];
      targetY = dataGroup[i][1];

      cout << "Target Y: " << targetY << endl;

      // current position
      result = cp.currentPosition(counts1,counts2);

      currrentX = result[0];
      currrentY = result[1];

      // cout << "Current X: " << result[0] << endl;
      cout << "Current Y: " << result[1] << endl;

      // x,y to counts
      result = mt.calCounts(targetX,targetY,currrentX,currrentY);
      
      targetCounts1 = result[0];
      targetCounts2 = result[1];

      cout << "targetCounts1:" << targetCounts1 << endl;
      cout << "targetCounts2:" << targetCounts2 << endl;

      counts1 = targetCounts1;
      counts2 = targetCounts2;

      // control the robot
      if(targetCounts1 > 0){
          dir1 = 1;
      }else{
          dir1 = 0;
      }
      if(targetCounts2 > 0){
          dir2 = 1;
      }else{
          dir2 = 0;
      }
      if (gpioInitialise() < 0)
      {
        fprintf(stderr, "igpio initialisation failed.\n\r");
      }
      else
      {
        fprintf(stderr, "igpio initialisation is okey.\n\r");
      }

      left_motor.run_left(speeds,dir1);
      right_motor.run_right(speeds,dir2);
      std::thread t1(&MotorL_Tread);
      std::thread t2(&MotorR_Tread);
      t1.join(); 
      t2.join();
    }

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

    gpioTerminate(); 
}
