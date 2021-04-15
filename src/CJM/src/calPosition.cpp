#include <iostream>
#include <cmath>
#include "../include/calPosition.h"
using namespace std;


// Find starting position
double calPosition::initialPosition(double L1,double L2)
{
    Z1 = L1 + Larm;
    Z2 = L2 + Larm;

    x = (Base*Base + Z1*Z1 - Z2*Z2)/(2*Base);
    y = sqrt(Z1*Z1-x*x);
    cout << "Test!!!! X: " << x << endl;
    cout << "Test!!!! Y: " << y << endl;
    return x, y;
}


// Calculate new robot position
double calPosition::currentPosition(int counts1, int counts2)
{
    double countsPerRadian = countsPerRevolution/(2*3.14); 

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

    return x,y;
}

