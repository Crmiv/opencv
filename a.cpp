#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<cv.hpp>
#include<highgui.h>

class Histogram1D{
	private:
		int histsize[1];
		float hranges[2];
		const float*ranges[1];
		int channels[1];
	

}
//# node address uchar* # data = image.data;

//get the nextline address, data += image.step; 

//clone image return an image object
//cv::Mat imageclone = image.clone();

//create the same image object
//image.create(OBJECT.rows,OBJECT.cols,OBJECT.type()) #or OBJECT.size

//three and more channels pix save and get
//image.at<cv::Vec3b>(i,j)[channel] = value

//get j,i pixel address
//&image.at(j,i)    
//another way, data = image.data + (j*image.step) + i*image.elemSize();

//get three channels iterator;
//cv::Mat_<cv::Vec3b>::const_iterator it=image.begin<cv::Vec3b>();

//get j row address
//image.ptr<uchar>(j);
//const int alpha_slider_max = 100;

//int alpha_slider;
//double alpha;
//double beta;
void salt(cv::Mat &image,int n);
void colorReduce(cv::Mat&image,int div);
void sharpen(const cv::Mat &start,cv::Mat &result);
void sharpen2D(const cv::Mat &image,cv::Mat &result);
//颜色衰减可以指定两个Mat 
//cv::Mat imageClone = image.clone();
int main(){
	cv::Mat image;//(1100,1100,CV_8U,cv::Scalar(200));
	cv::Mat result;//(1100,1100,CV_8U,cv::Scalar(200));
    image = cv::imread("/home/junningliu/img01.jpg");
//	colorReduce(image,30);
	cv::namedWindow("my");
	//std::cout<<"size,"<<image.size().height<<","<<image.size().width<<std::endl;
	//createTrackbar("track","my",100,100,100);
	int i = 1;
	sharpen2D(image,result);
	//cv::cvtColor(color,gray,CV_BGR2Gray);
	cv::imshow("my",result);
	cv::waitKey(50000);
	return 1;
}
//锐化拉普拉斯变换
void sharpen(const cv::Mat &start,cv::Mat &result)
{
	result.create(start.rows,start.cols,start.type());
	//handle all the rows except the first and the last
	int j,i;
	for(j=1;j<start.rows-1;j++)
	{
		const uchar* previous = start.ptr<uchar>(j-1);
		const uchar* current = start.ptr<uchar>(j);
		const uchar* next = start.ptr<uchar>(j+1);
		uchar *output = result.ptr<uchar>(j);
		for(i=1;i < (3*start.cols)-1;i++)
		{
			*output++ = cv::saturate_cast<uchar>(5*current[i] - current[i-1] - current[i+1] - previous[i] - next[i]);
		}
	}
		result.row(0).setTo(cv::Scalar(0));
		result.row(result.rows-1).setTo(cv::Scalar(0));
		result.col(result.cols-1).setTo(cv::Scalar(0));
		result.col(0).setTo(cv::Scalar(0));	
}
void sharpen2D(const cv::Mat &image,cv::Mat &result)
{
	cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
	kernel.at<float>(1,1)= 5.0;
	kernel.at<float>(0,1)= -1.0;
	kernel.at<float>(2,1)= -1.0;
	kernel.at<float>(1,0)= -1.0;
	kernel.at<float>(1,2)= -1.0;
	cv::filter2D(image,result,image.depth(),kernel);
}
// add point fun
void salt(cv::Mat &image,int n)
{
	for(int k=0;k<=n;k++)
	{
		int i = rand()%image.cols;
		int j = rand()%image.rows;
		if(image.channels() == 1){
		image.at<uchar>(j,i)=255;
		}else if(image.channels() == 3)
		{
			image.at<cv::Vec3b>(j,i)[0] = 255;
			image.at<cv::Vec3b>(j,i)[1] = 255;
			image.at<cv::Vec3b>(j,i)[2] = 255;	
		}
	}
}

//colorreduce fun
//other ways to achieve 
/*
 *data[i] = data[i]/div*div + div/2; 
 *data[i] = data[i] - data[i]%div +div/2;
 *use it to rounding pixel:
 *{
 * unchar mask = 0xFF<<n e.g.for div=16 mask=0xF0
 *}
 *reduce color fun->data[i]=data[i]&mask + div/2;
 * */

/*
 * #use iterator
 *void reducecolor(cv::Mat &image,int div = ??)
 {
 	get first place 
	cv::Mat_<cv::vec3b>::iterator it = image.begin<cv::Vec3b>();
	get end place
	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
 }
  */

/*void colorReduce(cv::Mat&image,int div)
{
	int nl = image.rows;
	int nc = image.cols*image.channels();
	int j = 0;
	for(;j<nl;j++)
	{
//	get row pointer
		uchar* data = image.ptr<uchar>(j);
		int i = 0;
		for(;i<nc;i++)
			{
				data[i]  =data[i]/div*div+div/2;
				/*data++ = *data/div*div+div/2;
			}
	}
}
*/
//颜色缩减函数非in_place变换

