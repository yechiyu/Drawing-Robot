#include "../include/pixtoMeter.h"


 void pixToM(){
     // drawing
    string Y,X;
    ifstream fin("PixData.txt"); 
    const int LINE_LENGTH = 1190;
    char str[LINE_LENGTH];  
    char *p;
	const char *delim = ",";
    const char *delim1 = "[";
    const char *delim2 = "]";
    int m =0;
    ofstream fout("MeterData.txt");
    while( fin.getline(str,LINE_LENGTH) )
    {    
        m++;
        p = strtok(str, delim1);
        p = strtok(p, delim2);
        p = strtok(p, delim);
        X = p;
        while(p) {
              Y = p;
              p = strtok(NULL, delim);
        }
        // cout <<"X:"<< X << endl;
        // cout <<"Y:"<< Y << endl;
        double xPix = stod(X);
        double yPix = stod(Y);
        // cout << "xPix:" << xPix << endl;
        // cout << "yPix:" << yPix << endl;

        double xLim[2] = {0.2,0.47};
        double yLim[2] = {0.2,0.47};
    
        double fraction = 0.8;

        double xLimPix[2] = {15,209}; // obatin from the pic
        double yLimPix[2] = {19,205};

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
        
        double coorsMemterX = pix2M*(xPix - xMinPix) + drawingOriginM[0];
        double coorsMemterY = pix2M*(yPix - yMinPix) + drawingOriginM[1];

        fout << coorsMemterX << " " << coorsMemterY << endl;
        // fout << coorsMemterX << endl;
        // fout << coorsMemterY << endl;
    }
 }
