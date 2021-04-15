#include <iostream>
#include <cmath>
#include "../include/calPosition.h"
#include "../include/movetoTarget.h"
using namespace std;

calPosition cp;
movetoTarget mt;


int main()
{
    double L1 = 0.425; //the distances between the motors and the pulley（left）
    double L2 = 0.425; //the distances between the motors and the pulley（right）
    int counts1 = 300; //the encoders give motor positions in counts
    int counts2 = 300;
    double targetX = 0.4; // target x
    double targetY = 0.3;  // target y

    double y = cp.initialPosition(L1,L2);

    // cout << "Starting X: " << x << endl;
    cout << "Starting Y: " << y << endl;

    double x1, y1 = cp.currentPosition(counts1,counts2);

    cout << "New X: " << x1 << endl;
    cout << "New Y: " << y1 << endl;
    cout << "--------------------------------------------" << endl;

    mt.calCounts(targetX,targetY,x1, y1);
    
    cout << "targetC1:" << mt.targetC1 << endl;
    cout << "targetC2:" << mt.targetC2 << endl;
}