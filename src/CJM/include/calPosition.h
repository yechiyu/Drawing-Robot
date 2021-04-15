#ifndef CALPOSTISION_H
#define CALPOSTISION_H

class calPosition {
    private:       
        double Base = 0.8;  // the distance between the two pulleys（0.535）
        double r_spool = 0.0045;    //the radius of the spool
        double Larm = 0.075;     
        int countsPerRevolution = 1200;     // the gear ratio is 100, the encoder spec are 12 counts per revolution
        double angle1, angle2, dStringLength1, dStringLength2, Z1, Z2, dZ1, dZ2, x, y;
        double result[2];

    public:
        double* initialPosition(double L1,double L2);
        double* currentPosition(int counts1, int counts2);
};
#endif