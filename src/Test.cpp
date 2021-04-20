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
}