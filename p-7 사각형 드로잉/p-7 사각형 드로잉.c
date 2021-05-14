#include<cv.h>
#include<highgui.h>
#include<stdbool.h>

CvRect box;																		//����ü ���� ���� 
bool DrawingBox = false;														//�̺�Ʈ ������ 

void MouseCallBack(int event, int x, int y, int flags, void*param);				//���콺�̺�Ʈ�����Լ� �� ���� 
void DrawBox(IplImage*img,CvRect rect);											//�簢���׸��� �ڽ� �� ���� 

int main()
{
	box = cvRect(-1,-1,0,0);													//����ü�� ��� x,y,���� ���̸� ���� �����Ѵ�. 
	IplImage*image = cvCreateImage(cvSize(200,200),IPL_DEPTH_8U,3);				//�����̹����� �����Ѵ�. 
	cvZero(image);																//�����Ѵ�.(�������) 
	IplImage*temp = cvCloneImage(image);										//�̹����� �����Ѵ�. 
	
	cvNamedWindow("Box",1);
	
	cvSetMouseCallback("Box",MouseCallBack,(void*)image);						//���콺�̺�Ʈ�� �����Ѵ�.(MouseCallBack�� ���� image�� ���) 
	
	
	while(1)
	{
		cvCopy(image,temp,0);													//�̹��� ���� 
		if(DrawingBox)DrawBox(temp,box);										//�����̹����� ����� 
		cvShowImage("Box",temp);												//�̹������ 
		if(cvWaitKey(15)==27)break;
	}
	
	cvReleaseImage(&image);
	cvReleaseImage(&temp);
	cvDestroyAllWindows();
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

