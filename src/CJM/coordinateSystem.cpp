#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    // Find starting position

    double Base = 80;// the distance between the two pulleys（53.5）
    double L1 = 42.5; //the distances between the motors and the pulley（left）
    double L2 = 42.5; //the distances between the motors and the pulley（right）
    double Larm = 7.5;

    double Z1, Z2, x, y;

    Z1 = L1 + Larm;
    Z2 = L2 + Larm;

    x = (Base*Base + Z1*Z1 - Z2*Z2)/(2*Base);
    y = sqrt(Z1*Z1-x*x);

    cout << "Starting X: " << x << endl;
    cout << "Starting Y: " << y << endl;



    // Calculate new robot position

    int counts1 = 120; //the encoders give motor positions in counts
    int counts2 = 80;

    int countsPerRevolution = 1200; // the gear ratio is 100, the encoder spec are 12 counts per revolution
    float countsPerRadian = countsPerRevolution/(2*3.14); 
    float r_spool = 0.45; //the radius of the spool

    double angle1, angle2, dStringLength1, dStringLength2, dZ1, dZ2;

    angle1 = counts1/countsPerRadian;
    angle2 = counts2/countsPerRadian;

    dStringLength1 = r_spool*angle1;
    dStringLength2 = r_spool*angle2;

    dZ1 = dStringLength1/2;
    dZ2 = dStringLength2/2;

    Z1 = Z1 + dZ1;
    Z2 = Z2 + dZ2;

    x = (Base*Base + Z1*Z1 - Z2*Z2)/(2*Base);
    y = sqrt(Z1*Z1-x*x);

    cout << "New X: " << x << endl;
    cout << "New Y: " << y << endl;

    return 0;
}

