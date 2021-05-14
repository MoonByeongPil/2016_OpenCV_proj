#include <cv.h>
#include <highgui.h>

int main()
{	
    IplImage* image1 = 0;														//이미지 구조체 포인터변수선언 
	IplImage* image2 = 0;
	
    CvCapture* capture1 = 0;  													//캡쳐 이미지 구조체 포인터변수선언 
    CvCapture* capture2 = 0;  
    
	capture1 = cvCaptureFromCAM(0);												//캡쳐 이미지 구조체 포인터변수에 각각 카메라 할당 
	capture2 = cvCaptureFromCAM(1);
	

	cvNamedWindow( "cam1", 0 );													//화면출력 윈도우 생성 
	cvResizeWindow( "cam1", 320, 240 );
	
    cvNamedWindow( "cam2", 0 );
	cvResizeWindow( "cam2", 320, 240 );
    
	while(1)
    {
        if( (!cvGrabFrame( capture1 ))||(!cvGrabFrame( capture2 )))				//프레임드랍시 브레이크 
          break;

        image1 = cvRetrieveFrame( capture1,1 );									//image에 프레임저장 
        image2 = cvRetrieveFrame( capture2,1 );
        
		cvShowImage( "cam1", image1 );											//이미지 출력 
		cvShowImage( "cam2", image2 );
		

        if( cvWaitKey(10) >= 0 )
            break;
    }

	cvReleaseCapture( &capture1 );												//이미지 릴리즈 및 모든창 닫기 
    cvReleaseCapture( &capture2 );
    
    cvReleaseImage(&image1);
    cvReleaseImage(&image2);
    
    cvDestroyAllWindows();
}
