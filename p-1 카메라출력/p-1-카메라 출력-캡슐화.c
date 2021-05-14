#include <cv.h>
#include <highgui.h>


void ucvViewCam(IplImage*image, CvCapture* capture, int SizeType, char *WindowName)
{
	if( capture )										//캡쳐값이 존재할경우 
	{    					
        image = cvRetrieveFrame( capture,1 );		//image에 capture에 받아온 단일 프레임을 저장 
		cvShowImage( WindowName, image );				//image를 camera창에 표시  		     
    }
}

int main()
{
	IplImage*image;
	
	CvCapture* capture;  							//캡쳐 이미지 구조체 포인터 변수 선언  
	capture = cvCaptureFromCAM(0);						//capture에 0번 카메라 입력 연결을 선언 
	
	cvNamedWindow( WindowName, SizeType );
	
	while(1)
	{
		ucvCamView(image,capture,1,"camera");
		
		if( cvWaitKey(10) >= 0 )
            break;
	}
    cvReleaseCapture( &capture );					//이미지 릴리스 
	cvReleaseImage( &image );						
    cvDestroyAllWindows();
	
}
