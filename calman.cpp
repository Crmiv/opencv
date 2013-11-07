#include<iostream>
#include<cv.h>
#include<cxcore.h>
#include<highgui.h>
#include<cmath>
#include<vector>
using namespca std;
const int WinHeight = 600;
const int WinWidth = 800;

CvPoint mousePosition=cvPoint(WinWidth>>1,WinHeight>>1);

void mouseEvent(int event,int x,int y,int flags,void *param)
{
	if(event==CV_EVENT_MOUSEMOVE)
	{
		mousePosition=cvPoint(x,y);
	}
}
int main(void)
{
 const int state_num = 4;
 const int measure_num = 2;
 CvKalman* kalman = cvCreateKalman(state_num,measure_num,0);
 CvMat* process_noise = cvCreateMat(state_num,1,CV_32FC1);
 CvMat* measurement = cvCreateMat(measure_num,1,CV_32FC1);
 CvRNG rng = cvRNG(-1);
 float A[state_nume][state_num] = {
 1,0,1,0
 0,1,0,1
 0,0,1,0
 0,0,0,1
 };

 memcpy(kalman->transition_matrix->data.fl,A,sizeof(A));
 cvSetIdentity(kalman->measurement_matrix,cvRealScalar(1));
 cvSetIdentity(kalman->process_noise_cov,cvRealScalar(1e-5));
 cvSetIdentity(kalman->measurement_noise_cov,cvRealScalar(1e-1));
 cvSetIdentity(kalman->error_cov_post,cvRealScalar(1));
 cvRandArr(&rng,kalman->state_post,CV_RAND_UNI,cvRealScalar(0),cvRealScalar(WinHeight>WinWidth?WinWidth:WinHeight));
 CvFont font;
 cvInitFont(&font,CV_FONT_HERSHEY_SCRIPT_COMPLEX,1,1);
 cvNamedWindow("kalman");
 cvSetMouseCallback("kalman",mouseEvent);
 IplImage* img = cvCreateImage(cvSize(WinWidth,WinHeight),8,3);
 while(1)
 {
 const CvMat* prediction = cvKalmanPredict(kalman,0);
 CvPoint predict_pt = cvPoint((int)prediction->data.fl[0],(int)prediction->data.fl[1]);
 measurement->data.fl[0] = (float)mousePosition.x;
 measurement->data.fl[1] = (float)mousePosition.y;

 cvKalmanCorrect(Kalman,measurement);

 cvSet(img,cvScalar(255,255,255,0));
 cvCircle(img,predict_pt,5,CV_RGB(0,255,0),3);
 cvCircle(img,mousePosition,5,CV_RGB(255,0,0),3);
 char buf[255];
 sprintf_s(buf,256,"predicted position:(%3d,%3d)",predict_pt.x,predict_pt.y);
 cvPutText(img,buf,cvPoint(10,30),&font,CV_RGB(0,0,0));
 sprintf_s(buf,256,"current position:(%3d,%3d)",mousePosition.x,mousePosition.y);
 cvPutText(img,buf,cvPoint(10,60),&font,CV_RGB(0,0,0));

 cvShowImage("kalman",img);
 int key = cvWaitKey(3);
 if(key==27)
 {
 	break;
 }
 }
cvRealeaseImage(img);
cvRealeaseKalman(kalman);
return 0;
}






