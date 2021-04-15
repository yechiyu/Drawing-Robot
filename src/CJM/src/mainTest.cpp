#include <iostream>
#include <cmath>
#include "../include/calPosition.h"
#include "../include/movetoTarget.h"
using namespace std;

calPosition cp;
movetoTarget mt;
double *result;

int main()
{
    double L1 = 0.425; //the distances between the motors and the pulley（left）
    double L2 = 0.425; //the distances between the motors and the pulley（right）
    int counts1 = 300; //the encoders give motor positions in counts
    int counts2 = 300;
    double targetX = 0.4; // target x
    double targetY = 0.3;  // target y

    result = cp.initialPosition(L1,L2);

    cout << "Initial X: " << result[0] << endl;
    cout << "Initial Y: " << result[1] << endl;

    result = cp.currentPosition(counts1,counts2);

    cout << "Current X: " << result[0] << endl;
    cout << "Current Y: " << result[1] << endl;

    result = mt.calCounts(targetX,targetY,result[0], result[1]);
    
    cout << "Counts1:" << result[0] << endl;
    cout << "Counts2:" << result[0] << endl;
}