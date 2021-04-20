<<<<<<< HEAD
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

int main(){
    Mat src = imread("../img/1.jpg"); //convert the image to grayscale and read it
	imshow("src", src);
=======
#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function

int main( int argc, char** argv ) {

    cv::Mat imgOriginal;

    imgOriginal = cv::imread("../img/1.jpg"); 

    //cv::Mat img = cv::imread("building.jpg");
    if( imgOriginal.empty() ) return -1;
    cv::namedWindow( "Example1", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Example1", imgOriginal );
    cv::waitKey( 0 );
    cv::destroyWindow( "Example1" );
    return 0;
>>>>>>> 35a2f666681a0a2d3a466bda75796b15ca165b8d
}