#include "../include/calPosition.h"
#include "../include/movetoTarget.h"
#include "../include/processImages.h"
#include "../include/controlMotor.h"

calPosition cp;
movetoTarget mt;
processImages pi;

double *result;

int main()
{  
    
    double L1 = 0.425; //the distances between the motors and the pulley（left）
    double L2 = 0.425; //the distances between the motors and the pulley（right）
    
    // string url = "../img/3.jpg";

    extern int pos[2];
    int counts1 = pos[0]; //the encoders give motor positions in counts
    int counts2 = pos[1];

    double targetX = 0.44; // target x
    double targetY = 0.5;  // target y

    double currrentX, currrentY, targetCounts1, targetCounts2;

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
    // left_motor.run_left();
    // right_motor.run_right();
    // while (true){
    //     if(targetCounts1 == counts1){
    //         left_motor.stop_left();
    //         break;
    //     }else{
    //         cout << "counts" << counts1<< endl;
    //         cout << "targetcounts" << targetCounts1<< endl;
    //     }
    //     if(targetCounts2 == counts2){
    //         left_motor.stop_left();
    //         break;
    //     }else{
    //         cout << "running" << endl;
    //     }   
    // } 
    if (gpioInitialise() < 0)
    {
      fprintf(stderr, "igpio initialisation failed.\n\r");
     }
    else
    {
      fprintf(stderr, "igpio initialisation is okey.\n\r");
    }
    control left_motor(26,19,callback_left,20,21,150,1);
    control right_motor(7,8,callback_right,6,13,87,1);

    left_motor.run_left();
    right_motor.run_right();
    cout << counts1 << endl;
    cout << counts2 << endl;
    while(counts1 == 600){
        left_motor.stop_left();
        right_motor.stop_right();
    }
    gpioTerminate(); 
}