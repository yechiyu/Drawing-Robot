#include <iostream>
#include <cmath>
#include "../include/movetoTarget.h"
using namespace std;

// Move to target position
double* movetoTarget::calCounts(double targetX, double targetY, double x, double y)
{
    double Z1 = sqrt(x*x+y*y);
    double Z2 = sqrt((Base - x)*(Base - x) + y*y);

    targetZ1 = sqrt(targetX*targetX+targetY*targetY);
    targetZ2 = sqrt((Base - targetX)*(Base - targetX) + targetY*targetY);
    
    dZ1 = targetZ1 - Z1;
    dZ2 = targetZ2 - Z2;

    dStringLength1 = 2*dZ1;
    dStringLength2 = 2*dZ2;

    angle1 = dStringLength1/(r_spool*2*3.14);
    angle2 = dStringLength2/(r_spool*2*3.14);

    angle1 = angle1*100; // the gear ratio is 100
    angle2 = angle2*100;
    
    cout << "Angle1:" << angle1 << endl;

    targetC1 = angle1*12/4;
    targetC2 = angle2*12/4;  


    result[0] = targetC1;
    result[1] = targetC2;


    return result; 
}