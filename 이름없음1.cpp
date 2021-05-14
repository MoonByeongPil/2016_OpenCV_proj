#include<cv.h>
#include<highgui.h>

int main()
{
	IplImage*image=cvLoadImage("p-3_tamplet",-1);
	int size[3]={256,256,256}
	CvHistogram *hist=cvCreateHist(3,size,CV_HIST_SPARSE,768,1);
	cvCalcHist(*image,hist);
}
