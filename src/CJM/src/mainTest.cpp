#include "../include/calPosition.h"
#include "../include/movetoTarget.h"
#include "../include/processImages.h"

calPosition cp;
movetoTarget mt;
processImages pi;

double *result;

int main()
{  
    double L1 = 0.425; //the distances between the motors and the pulley（left）
    double L2 = 0.425; //the distances between the motors and the pulley（right）
    string url = "../img/3.jpg";

    int counts1 = 300; //the encoders give motor positions in counts
    int counts2 = 300;
    double targetX = 0.4; // target x
    double targetY = 0.3;  // target y

    double currrentX, currrentY, targetCounts1, targetCounts2;


    result = cp.initialPosition(L1,L2);

    cout << "Initial X: " << result[0] << endl;
    cout << "Initial Y: " << result[1] << endl;

    result = cp.currentPosition(counts1,counts2);

    currrentX = result[0];
    currrentY = result[1];

    cout << "Current X: " << result[0] << endl;
    cout << "Current Y: " << result[1] << endl;

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

    result = mt.calCounts(targetX,targetY,result[0], result[1]);
    
    targetCounts1 = result[0];
    targetCounts2 = result[1];

    cout << "Counts1:" << result[0] << endl;
    cout << "Counts2:" << result[1] << endl;

    // run();
    if((currrentX-targetX<0.000001)&&(currrentY-targetY)<0.000001)
        // stop();
        cout << "Stop"<< endl;
    else 
        // run();
        cout << "Running"<< endl;

}