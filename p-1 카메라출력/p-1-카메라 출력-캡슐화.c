#include <cv.h>
#include <highgui.h>


void ucvViewCam(IplImage*image, CvCapture* capture, int SizeType, char *WindowName)
{
	if( capture )										//ĸ�İ��� �����Ұ�� 
	{    					
        image = cvRetrieveFrame( capture,1 );		//image�� capture�� �޾ƿ� ���� �������� ���� 
		cvShowImage( WindowName, image );				//image�� cameraâ�� ǥ��  		     
    }
}

int main()
{
	IplImage*image;
	
	CvCapture* capture;  							//ĸ�� �̹��� ����ü ������ ���� ����  
	capture = cvCaptureFromCAM(0);						//capture�� 0�� ī�޶� �Է� ������ ���� 
	
	cvNamedWindow( WindowName, SizeType );
	
	while(1)
	{
		ucvCamView(image,capture,1,"camera");
		
		if( cvWaitKey(10) >= 0 )
            break;
	}
    cvReleaseCapture( &capture );					//�̹��� ������ 
	cvReleaseImage( &image );						
    cvDestroyAllWindows();
	
}
