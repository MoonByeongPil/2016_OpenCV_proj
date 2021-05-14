#include <cv.h>
#include <highgui.h>
#include <stdio.h>

int main()
{
    IplImage* image = 0;								//�̹��� ����ü ������ �������� 

    CvCapture* capture = 0;  							//ĸ�� �̹��� ����ü ������ ���� ����  
	capture = cvCaptureFromCAM(0);						//capture�� 0�� ī�޶� �Է� ������ ���� 
	

	if( capture )										//ĸ�İ��� �����Ұ�� 
	{
    	cvNamedWindow( "camera", 1 );					//������ ����  
		cvResizeWindow( "camera", 640,480 );			//������ ������ 
        
		while(1)										
        {
            if( !cvGrabFrame( capture ))				//�������� ��ӵǸ� ���α׷� ���� 
                break;

            image = cvRetrieveFrame( capture,1 );		//image�� capture�� �޾ƿ� ���� �������� ���� 
			cvShowImage( "camera", image );				//image�� cameraâ�� ǥ��  
			
		

            if( cvWaitKey(10) >= 0 )					//esc�� �극��ũ 
                break;
        }
        cvReleaseCapture( &capture );					//�̹��� ������ 
		cvReleaseImage( &image );						
        cvDestroyWindow( "camera" );
	}
}
