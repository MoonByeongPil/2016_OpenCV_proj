#include <cv.h>
#include <highgui.h>

int main()
{	
    IplImage* image1 = 0;														//�̹��� ����ü �����ͺ������� 
	IplImage* image2 = 0;
	
    CvCapture* capture1 = 0;  													//ĸ�� �̹��� ����ü �����ͺ������� 
    CvCapture* capture2 = 0;  
    
	capture1 = cvCaptureFromCAM(0);												//ĸ�� �̹��� ����ü �����ͺ����� ���� ī�޶� �Ҵ� 
	capture2 = cvCaptureFromCAM(1);
	

	cvNamedWindow( "cam1", 0 );													//ȭ����� ������ ���� 
	cvResizeWindow( "cam1", 320, 240 );
	
    cvNamedWindow( "cam2", 0 );
	cvResizeWindow( "cam2", 320, 240 );
    
	while(1)
    {
        if( (!cvGrabFrame( capture1 ))||(!cvGrabFrame( capture2 )))				//�����ӵ���� �극��ũ 
          break;

        image1 = cvRetrieveFrame( capture1,1 );									//image�� ���������� 
        image2 = cvRetrieveFrame( capture2,1 );
        
		cvShowImage( "cam1", image1 );											//�̹��� ��� 
		cvShowImage( "cam2", image2 );
		

        if( cvWaitKey(10) >= 0 )
            break;
    }

	cvReleaseCapture( &capture1 );												//�̹��� ������ �� ���â �ݱ� 
    cvReleaseCapture( &capture2 );
    
    cvReleaseImage(&image1);
    cvReleaseImage(&image2);
    
    cvDestroyAllWindows();
}
