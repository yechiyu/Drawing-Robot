#ifndef PROCESSIMAGES_H
#define PROCESSIMAGES_H

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

class processImages {
    private:    
        int nRows;
        int nCols;
    public:
        int process(string url);
        int i;
        int pointImg[][2];
};
#endif