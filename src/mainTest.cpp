#include "../include/calPosition.h"
#include "../include/movetoTarget.h"
#include "../include/processImages.h"
#include "../include/controlMotor.h"
#include "../include/dataTest.h"
#include <iostream>
#include <thread>
#include <stdlib.h>
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
      Pi_servo(1950);
      usleep(200000);
      Pi_servo(1500);
      usleep(200000);
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
      Pi_servo(1950);
      usleep(200000);
      Pi_servo(1500);
      usleep(200000);
   }
    
int main() 
{  
    
    double L1 = 0.25; //the distances between the motors and the pulley（left）
    double L2 = 0.25; //the distances between the motors and the pulley（right）
    
    int speeds = 50;
    bool dir1,dir2;
    double speed1,speed2;
    // string url = "../img/1.jpg";

    int counts1 = 0; //the encoders give motor positions in counts
    int counts2 = 0;

    double targetX; // target x
    double targetY;  // target y

    double currrentX, currrentY, initialX, initialY;

    // intial position
    result = cp.initialPosition(L1,L2);

    initialX = result[0];
    initialY = result[1];

    // cout << "Initial X: " << result[0] << endl;
    // cout << "Initial Y: " << result[1] << endl;

    // drawing
    pi.process();
    string Y,X;
    ifstream fin("data.txt"); 
    const int LINE_LENGTH = 100; 
    char str[LINE_LENGTH];  
    char *p;
	  const char *delim = " ";
    int m =0;
    while( fin.getline(str,LINE_LENGTH) )
    {    
        cout <<"--------------------------"<< m <<"--------------------------"<< endl;
        m++;
        cout << str << endl;
        p = strtok(str, delim);
        X = p;
        while(p) {
              Y = p;
              p = strtok(NULL, delim);
        }
        // cout <<"X:"<< X << endl;
        // cout <<"Y:"<< Y << endl;
        targetX = stod(X);
        targetY = stod(Y);


        cout << "Target Y: " << targetY << endl;

        // current position
        if(counts1==0 && counts2==0){
          currrentX = initialX;
          currrentY = initialY;
        }else{
          result = cp.currentPosition(counts1,counts2);
          currrentX = result[0];
          currrentY = result[1];
        }
        cout << "Current X: " << result[0] << endl;
        cout << "Current Y: " << result[1] << endl;  

        // x,y to counts
        result = mt.calCounts(targetX,targetY,currrentX,currrentY);
        
        targetCounts1 = result[0];
        targetCounts2 = result[1];

        cout << "targetCounts1:" << targetCounts1 << endl;
        cout << "targetCounts2:" << targetCounts2 << endl;

        counts1 = targetCounts1;
        counts2 = targetCounts2;

        // calculate the speed factor
        double speedFactor = double(abs(targetCounts2))/double(abs(targetCounts1));
        if(speedFactor>1){
            speed1 = speeds;
            speed2 = speeds*speedFactor;
        }else{
            speed2 = speeds;
            speed1 = speeds/speedFactor;
        }

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
        cout << "!!!!speed" << speed1 << "," << speed2 <<endl;
        if (speed1>255) speed1=255;
        if (speed2>255) speed2=255;
        // left_motor.run_left(int(speed1),dir1);
        // right_motor.run_right(int(speed2),dir2);
        // std::thread t1(&MotorL_Tread);
        // std::thread t2(&MotorR_Tread);
        // t1.join(); 
        // t2.join();
    }
    gpioTerminate(); 
}
