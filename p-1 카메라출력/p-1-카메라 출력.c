#include <cv.h>
#include <highgui.h>
#include <stdio.h>

int main()
{
    IplImage* image = 0;								//이미지 구조체 포인터 변수선언 

    CvCapture* capture = 0;  							//캡쳐 이미지 구조체 포인터 변수 선언  
	capture = cvCaptureFromCAM(0);						//capture에 0번 카메라 입력 연결을 선언 
	

	if( capture )										//캡쳐값이 존재할경우 
	{
    	cvNamedWindow( "camera", 1 );					//윈도우 생성  
		cvResizeWindow( "camera", 640,480 );			//윈도우 사이즈 
        
		while(1)										
        {
            if( !cvGrabFrame( capture ))				//프레임이 드롭되면 프로그램 종료 
                break;

            image = cvRetrieveFrame( capture,1 );		//image에 capture에 받아온 단일 프레임을 저장 
			cvShowImage( "camera", image );				//image를 camera창에 표시  
			
		

            if( cvWaitKey(10) >= 0 )					//esc에 브레이크 
                break;
        }
        cvReleaseCapture( &capture );					//이미지 릴리스 
		cvReleaseImage( &image );						
        cvDestroyWindow( "camera" );
	}
}
