#include "../include/define.h"


        
int speeds = 50;
bool dir1,dir2;
double speed1,speed2;
        // string url = "../img/1.jpg";

int counts1 = 0; //the encoders give motor positions in counts
int counts2 = 0;

double targetX; // target x
double targetY;  // target y

double currrentX, currrentY, initialX, initialY;
int main() 
{  
    double L1 = 0.260; //the distances between the motors and the pulley（left）
    double L2 = 0.250; //the distances between the motors and the pulley（right）
    process();
    pixToM();
    // intial position
    result = cp.initialPosition(L1,L2);
    initialX = result[0];
    initialY = result[1];

    // Drawing start 
    string Y,X;
    ifstream fin("newData.txt"); 
    const int LINE_LENGTH = 437; 
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
        
        targetX = stod(X);
        targetY = stod(Y);

        // cout << "Target X: " << targetX << endl;
        // cout << "Target Y: " << targetY << endl;

        // current position
        if(counts1==0 && counts2==0){
          currrentX = initialX;
          currrentY = initialY;
        }else{
          result = cp.currentPosition(counts1,counts2);
          currrentX = result[0];
          currrentY = result[1];
        }
        // cout << "Current X: " << result[0] << endl;
        // cout << "Current Y: " << result[1] << endl;  

        // x,y to counts
        result = mt.calCounts(targetX,targetY,currrentX,currrentY);
        
        targetCounts1 = result[0];
        targetCounts2 = result[1];

        // cout << "targetCounts1:" << targetCounts1 << endl;
        // cout << "targetCounts2:" << targetCounts2 << endl;

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

        if (speed1>255) speed1=255;
        if (speed2>255) speed2=255;

        // control the direction of robot
        if(targetCounts1 > 0){
            dir1 = 0;
        }else{
            dir1 = 1;
        }
        if(targetCounts2 > 0){
            dir2 = 1;
        }else{
            dir2 = 0;
        }
        
        // initialise
        if (gpioInitialise() < 0)
        {
          fprintf(stderr, "igpio initialisation failed.\n\r");
        }
        else
        {
          fprintf(stderr, "igpio initialisation is okey.\n\r");
        }
        // cout << "!!!!speed" << df.speed1 << "," << df.speed2 <<endl;
        
        // run
        
        // left_motor.run_left(50,0);
        // usleep(2000000);
        // left_motor.stop_left();
        // right_motor.run_right(70,0);
        // usleep(2000000);
        // right_motor.stop_left();
        // gpioTerminate(); 
        left_motor.run_left(int(speed1),dir1);
        right_motor.run_right(int(speed2),dir2);
        std::thread t1(&MotorL_Tread);
        std::thread t2(&MotorR_Tread);
        t1.join(); 
        t2.join();
        // Pi_servo(1950);
        // usleep(100000);
        // Pi_servo(1500);
        // usleep(100000);
        // // gpioTerminate(); 
    }
    gpioTerminate(); 
}
