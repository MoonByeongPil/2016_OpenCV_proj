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
	
	double min, max;																								//최댓값, 최솟값 실수변수선언 
	CvPoint left_top;																								//이미지 기준 왼쪽 위 


	while(1)
	{
		
		A = cvRetrieveFrame( capture,1 );																			//a 에 이미지 저장 
		Show("t",A)	;																								//a 표시 
		B = cvLoadImage("p-3_tamplet.jpg", -1);																		//샘플 이미지 로딩 
		C = cvCreateImage( cvSize( A->width - B->width+1, A->height - B->height+1 ), IPL_DEPTH_32F, 1 );			//상관계수 표시용 이미지 생성 
		
		cvMatchTemplate(A, B, C, CV_TM_CCOEFF_NORMED);																//상관계수 비교 매칭 
		cvMinMaxLoc(C, &min, &max, NULL, &left_top,0);																//c에 상관계수 맵 드로잉 
		cvRectangle(A, left_top, cvPoint(left_top.x + B->width, left_top.y + B->height), CV_RGB(255,0,0),0,0,0);	//a에 해당위치에 사각형 드로잉 
		
		Show("result",A);																							//결과, 샘플, 상관계수 출력 
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
