#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

int main(){
    Mat src = imread("../img/1.jpg"); //convert the image to grayscale and read it
	imshow("src", src);
}