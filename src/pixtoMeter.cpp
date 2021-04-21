#include "../include/pixtoMeter.h"


 void pixToM(){
     // drawing
    string Y,X;
    ifstream fin("../dataTest/data.txt"); 
    const int LINE_LENGTH = 380;
    char str[LINE_LENGTH];  
    char *p;
	  const char *delim = " ";
    int m =0;
    ofstream fout("newData.txt");
    while( fin.getline(str,LINE_LENGTH) )
    {    
        cout <<"--------------------------"<< m <<"--------------------------"<< endl;
        m++;
        p = strtok(str, delim);
        X = p;
        while(p) {
              Y = p;
              p = strtok(NULL, delim);
        }
        cout <<"X:"<< X << endl;
        cout <<"Y:"<< Y << endl;
        double xPix = stod(X);
        double yPix = stod(Y);
        // cout << "xPix:" << xPix << endl;
        // cout << "yPix:" << yPix << endl;

        double xLim[2] = {0.06,0.480};
        double yLim[2] = {0.2,0.46};
    
        double fraction = 0.6;

        double xLimPix[2] = {244,397}; // obatin from the pic
        double yLimPix[2] = {146,275};

        double xMinM = xLim[0];
        double yMinM = yLim[0];

        double xRangeM = xLim[1] - xLim[0];
        double yRangeM = yLim[1] - yLim[0];

        double xMinPix = xLimPix[0];
        double yMinPix = yLimPix[0];

        double xRangePix = xLimPix[1] - xLimPix[0];
        double yRangePix = yLimPix[1] - yLimPix[0];

        double xScaleFactor = fraction*xRangeM/xRangePix;
        double yScaleFactor = fraction*yRangeM/yRangePix;

        double pix2M = std::min(xScaleFactor,yScaleFactor);

        if(pix2M == NAN){
            pix2M = 0;
        }

        double centerMeters[2];
        centerMeters[0] = xMinM + xRangeM/2;
        centerMeters[1] = yMinM + yRangeM/2;

        double drawingOriginM[2];
        drawingOriginM[0] = centerMeters[0] - pix2M*xRangePix/2;
        drawingOriginM[1] = centerMeters[1] - pix2M*yRangePix/2;

        int n = 380;
        double segmentsMeters[380][2] = {0};// 
        int nSegments = n;
        
        double coorsMemterX = pix2M*(xPix - xMinPix) + drawingOriginM[0];
        double coorsMemterY = pix2M*(yPix - yMinPix) + drawingOriginM[1];

        fout << coorsMemterX << " " << coorsMemterY << endl;
    }
 }
