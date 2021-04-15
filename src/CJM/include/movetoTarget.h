#ifndef MOVE_H
#define MOVE_H

class movetoTarget {
    private:
        double Base = 0.8;  // the distance between the two pulleys（0.535）
        double r_spool = 0.0045;    //the radius of the spool
        double x, y, angle1, angle2, dStringLength1, dStringLength2, dZ1, dZ2, targetZ1, targetZ2;

    public:
        double targetC1, targetC2;
        int calCounts(double targetX, double targetY, double x, double y);
};
#endif