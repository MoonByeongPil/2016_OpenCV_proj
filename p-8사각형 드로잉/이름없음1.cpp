#include <cv.h>
#include <highgui.h>
#include <stdio.h>

CvRect box;																		//����ü ���� ���� 
bool DrawingBox = false;														//�̺�Ʈ ������ 

void MouseCallBack(int event, int x, int y, int flags, void*param);				//���콺�̺�Ʈ�����Լ� �� ���� 
void DrawBox(IplImage*img,CvRect rect);											//�簢���׸��� �ڽ� �� ���� 

int main()
{
    IplImage* image = 0;								//�̹��� ����ü ������ �������� 
	IplImage* resault = 0;
	
    CvCapture* capture = 0;  							//ĸ�� �̹��� ����ü ������ ���� ����  
	capture = cvCaptureFromCAM(0);						//capture�� 0�� ī�޶� �Է� ������ ���� 
	
	cvGrabFrame( capture );
	image = cvRetrieveFrame( capture,1 );
	
	box = cvRect(-1,-1,0,0);
	IplImage*temp = cvCloneImage(image);
	
	if( capture )										//ĸ�İ��� �����Ұ��
	{
	
    	cvNamedWindow( "camera", 1 );					//������ ����  
		cvNamedWindow("Box",1);

        cvSetMouseCallback("camera",MouseCallBack,(void*)image);	
        
		while(1)										
        {
            if( !cvGrabFrame( capture ))				//�������� ��ӵǸ� ���α׷� ���� 
                break;

            image = cvRetrieveFrame( capture,1 );		//image�� capture�� �޾ƿ� ���� �������� ���� 
            cvCopy(image,temp,0);
            
            if(DrawingBox)
			{	
				
				DrawBox(image,box);										//�����̹����� ����� 
				DrawBox(temp,box);
				resault=cvCreateImage(cvSize(box.width,box.height),IPL_DEPTH_32F,3);

				
				cvShowImage("Box",temp);
			}
			cvShowImage( "camera", image );				//image�� cameraâ�� ǥ��  
			
		

            if(cvWaitKey(15)==27)break;
        }
        cvReleaseCapture( &capture );					//�̹��� ������ 
		cvReleaseImage( &image );	
		cvReleaseImage( &temp );					
        cvDestroyAllWindows();
	}
}

void MouseCallBack(int event, int x, int y, int flags, void*param)
{
	IplImage*image=(IplImage*)param;
	switch(event)
	{
		case CV_EVENT_MOUSEMOVE:												//���콺�� �����̸� �ڽ��� ���̴� �ʱ�x-���콺x 
			{
				if(DrawingBox)
				{
					box.width = x - box.x;
					box.height = y - box.y;
				}
			}break;
			
		case CV_EVENT_LBUTTONDOWN:												//���콺������ ����� 
			{
				DrawingBox=true;
				box = cvRect(x,y,0,0);
			}break;
			
		case CV_EVENT_LBUTTONUP:												//���콺���� ����� ���� 
			{
				DrawingBox=false;
				if(box.width<0)													//�ݴ�����ϰ�� ���� 
				{
					box.x+=box.width;
					box.width*=-1;
				}
				
				if(box.width<0)
				{
					box.y+=box.height;
					box.height*=-1;
				}
			}break;
	}
}

void DrawBox(IplImage*img,CvRect rect)
{
	cvRectangle(img,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),CV_RGB(255,0,0),5,0,0);
}
