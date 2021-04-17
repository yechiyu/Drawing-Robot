#include "../include/processImages.h"

int processImages::process(string url)
{
	Mat src = imread(url,0); //convert the image to grayscale and read it
	// imshow("src", src);
 
	Mat dst;
	threshold(src, dst, 100, 255, CV_THRESH_BINARY_INV);  // binary images
	// imshow("dst", dst);
 
	nRows = dst.rows;
	nCols = dst.cols;
 
	ofstream fout("data.txt");
	i = 0;
	// 2 layer loop traverse the picture, when no line, the pixel is 0;
	for(int w = 0; w < nCols; w++)
	{
		int sum = 0;
		
		for(int h = 0; h < nRows; h++)
		{
			uchar *pRow = dst.ptr<uchar>(h, w); // point
			sum += (int)(*pRow);
 
			if(sum > 0)
			{
				fout << "X:" << w << ",Y:" << h <<  endl; //save the data in text
				pointImg[i][0] = w;
				pointImg[i][1] = h;
				i++;
				sum = 0;
				break;
			}
		}
	}
	waitKey();
	cout << endl;
	return 0;
}