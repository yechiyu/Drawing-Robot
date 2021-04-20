#include "../include/processImages.h"
  
int processImages::process()
{
 Mat src = imread("../img/1.jpg", 0);
 //imshow("src", src);
  
 Mat dst;
 threshold(src, dst, 100, 255, CV_THRESH_BINARY_INV); //二值化
 //imshow("dst", dst);
  
 int nRows = dst.rows;
 int nCols = dst.cols;
  
 ofstream fout("originalData.txt");

 //按列扫描，求像素和，由于是二值后的图片，没有线条时，该列的像素和为0；扫描到线条时像素大于0
 for(int w = 0; w < nCols; w++)
 {
	int sum = 0;
	
	for(int h = 0; h < nRows; h++)
	{
		uchar *pRow = dst.ptr<uchar>(h, w); //该列中每个像素的地址
		sum += (int)(*pRow);
		
		if(sum > 0) //到达了线条的上侧，像素和大于0
		{
			// cout << "找到了线条点"<< i << endl;  //从上往下找，由于线条很细，目前只判断上边界。
			// cout << ",坐标如下： X = " << X << ", Y = " << Y << endl; 
			fout << w << " " << h << endl; //控制台会丢失数据，存到文本不会丢失
			sum = 0;
			break;
		}
	}
 }
  
 waitKey();
 cout << endl;
 system("pause");
 return 0;
}