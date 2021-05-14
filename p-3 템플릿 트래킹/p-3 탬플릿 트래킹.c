#include <cv.h>
#include <highgui.h>

void Show(char *str, IplImage *img)
{
	cvNamedWindow( str, 1);
	cvShowImage( str, img );
}

int main()
{
	IplImage*image=0;
	IplImage *A = 0;
	IplImage *B = 0;
	IplImage* C = 0;
																									
	CvCapture*capture=0; 
	capture=cvCaptureFromCAM(0);

	image=cvRetrieveFrame(capture,1);
	
	double min, max;																								//�ִ�, �ּڰ� �Ǽ��������� 
	CvPoint left_top;																								//�̹��� ���� ���� �� 


	while(1)
	{
		
		A = cvRetrieveFrame( capture,1 );																			//a �� �̹��� ���� 
		Show("t",A)	;																								//a ǥ�� 
		B = cvLoadImage("p-3_tamplet.jpg", -1);																		//���� �̹��� �ε� 
		C = cvCreateImage( cvSize( A->width - B->width+1, A->height - B->height+1 ), IPL_DEPTH_32F, 1 );			//������ ǥ�ÿ� �̹��� ���� 
		
		cvMatchTemplate(A, B, C, CV_TM_CCOEFF_NORMED);																//������ �� ��Ī 
		cvMinMaxLoc(C, &min, &max, NULL, &left_top,0);																//c�� ������ �� ����� 
		cvRectangle(A, left_top, cvPoint(left_top.x + B->width, left_top.y + B->height), CV_RGB(255,0,0),0,0,0);	//a�� �ش���ġ�� �簢�� ����� 
		
		Show("result",A);																							//���, ����, ������ ��� 
		Show("sample",B);	
		Show("C",C);			
		
		if( cvWaitKey(10) >= 0 )
		            break;
		if( !cvGrabFrame( capture ))
		            break;
	}

	cvReleaseImage(&image);
	cvReleaseCapture( &capture );

	cvReleaseImage(&A);
	cvReleaseImage(&B);
	cvReleaseImage(&C);


	cvDestroyAllWindows();
}
