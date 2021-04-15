#include <iostream>
#include <cmath>
using namespace std;


double Base = 0.8;// the distance between the two pulleys（0.535）
double Z1, Z2, x, y;
float r_spool = 0.0045; //the radius of the spool
double angle1, angle2, dStringLength1, dStringLength2, dZ1, dZ2;
double targetZ1, targetZ2, targetC1, targetC2;

// Find starting position
double initialPosition(double L1,double L2)
{

    double Larm = 0.075;

    Z1 = L1 + Larm;
    Z2 = L2 + Larm;

    x = (Base*Base + Z1*Z1 - Z2*Z2)/(2*Base);
    y = sqrt(Z1*Z1-x*x);

    // cout << "Starting Z1: " << Z1 << endl;  // using for test
    return x,y;
}

// Calculate new robot position
double currentPosition(int counts1, int counts2)
{

    int countsPerRevolution = 1200; // the gear ratio is 100, the encoder spec are 12 counts per revolution
    float countsPerRadian = countsPerRevolution/(2*3.14); 

    angle1 = counts1*4/countsPerRadian; // three orthogonal cycles, four changes in one cycle.
    angle2 = counts2*4/countsPerRadian;

    dStringLength1 = r_spool*angle1;
    dStringLength2 = r_spool*angle2;

    dZ1 = dStringLength1/2;
    dZ2 = dStringLength2/2;

    Z1 = Z1 + dZ1;
    Z2 = Z2 + dZ2;

    x = (Base*Base + Z1*Z1 - Z2*Z2)/(2*Base);
    y = sqrt(Z1*Z1-x*x);

    // cout << "New Z1: " << Z1 << endl;
    return x,y;
}

// Move to target position
int movetoTarget(double targetX, double targetY)
{
    x = targetX;
    y = targetY;

    targetZ1 = sqrt(x*x+y*y);
    targetZ2 = sqrt((Base - x)*(Base - x) + y*y);
    
    dZ1 = targetZ1 - Z1;
    dZ2 = targetZ2 - Z2;

    dStringLength1 = 2*dZ1;
    dStringLength2 = 2*dZ2;

    angle1 = dStringLength1/(r_spool*2*3.14);
    angle2 = dStringLength2/(r_spool*2*3.14);

    angle1 = angle1*100; // the gear ratio is 100
    angle2 = angle2*100;
    
    targetC1 = angle1*12/4;
    targetC2 = angle2*12/4;   
    
    return targetC1, targetC2;
}




int main()
{
    double L1 = 0.425; //the distances between the motors and the pulley（left）
    double L2 = 0.425; //the distances between the motors and the pulley（right）
    int counts1 = 300; //the encoders give motor positions in counts
    int counts2 = 300;
    double targetX = 0.4; // target x
    double targetY = 0.3;  // target y

    initialPosition(L1,L2);

    cout << "Starting X: " << x << endl;
    cout << "Starting Y: " << y << endl;

    currentPosition(counts1,counts2);

    cout << "New X: " << x << endl;
    cout << "New Y: " << y << endl;
    cout << "--------------------------------------------" << endl;

    movetoTarget(targetX,targetY);
    
    cout << "Test_c1:" << targetC1 << endl;
    cout << "Test_c2:" << targetC2 << endl;
}