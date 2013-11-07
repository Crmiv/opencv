#include<cv.h>
#include<iostream>
#include<highgui.h>

using namespace cv;

int main(int argc,char** argv)
{
	double alpha = 0.5;
	double beta; 
	double input;
	Mat src1,src2,dst;
	std::cin>>input;
	alpha = input;
	beta = 1-input;
	src1 = imread("/home/junningliu/下载/wall.jpg");
	src2 = imread("/home/junningliu/下载/wall.jpg");
	namedWindow("image",1);
	addWeighted(src1,alpha,src2,beta,0.0,dst);
	imshow("image",dst);
	waitKey(50000);
	return 0;
}
