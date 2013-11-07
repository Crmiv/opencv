#include<stdio.h>
#include<stdlib.h>
#include "cv.h"
#include "highgui.h"
void onMouse(int Event,int x,int y,int flags,void* param);
int main(void)
{
	CvCapture *capture;
	IplImage *frame;
	capture = cvCaptureFromCAM(0);
	cvNamedWindow("win",0);
	cvSetMouseCallback("win",onMouse,NULL);
		while(1)
		{
		frame = cvQueryFrame(capture);
		cvShowImage("win",frame);
		if(cvWaitKey(10) >= 0)
		{
			break;
		}
		}
	cvReleaseCapture(&capture);
	cvDestroyWindow("win");
	return 0;
}

void onMouse(int Event,int x,int y,int flags,void* param)
{
	printf("%d %d",Event,x,flags);
}
