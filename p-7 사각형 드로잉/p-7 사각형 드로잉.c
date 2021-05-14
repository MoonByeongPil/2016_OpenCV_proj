#include<cv.h>
#include<highgui.h>
#include<stdbool.h>

CvRect box;																		//구조체 참조 선언 
bool DrawingBox = false;														//이벤트 논리변수 

void MouseCallBack(int event, int x, int y, int flags, void*param);				//마우스이벤트정의함수 선 정의 
void DrawBox(IplImage*img,CvRect rect);											//사각형그리기 박스 선 정의 

int main()
{
	box = cvRect(-1,-1,0,0);													//구조체의 멤버 x,y,길이 높이를 각각 설정한다. 
	IplImage*image = cvCreateImage(cvSize(200,200),IPL_DEPTH_8U,3);				//바탕이미지를 생성한다. 
	cvZero(image);																//리셋한다.(검은배경) 
	IplImage*temp = cvCloneImage(image);										//이미지를 복사한다. 
	
	cvNamedWindow("Box",1);
	
	cvSetMouseCallback("Box",MouseCallBack,(void*)image);						//마우스이벤트를 정의한다.(MouseCallBack에 따라 image에 출력) 
	
	
	while(1)
	{
		cvCopy(image,temp,0);													//이미지 복사 
		if(DrawingBox)DrawBox(temp,box);										//복사이미지에 드로잉 
		cvShowImage("Box",temp);												//이미지출력 
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
		case CV_EVENT_MOUSEMOVE:												//마우스가 움직이면 박스의 길이는 초기x-마우스x 
		{
			if(DrawingBox)
			{
				box.width = x - box.x;
				box.height = y - box.y;
			}
		}break;
		
		case CV_EVENT_LBUTTONDOWN:												//마우스눌리면 드로잉 
		{
			DrawingBox=true;
			box = cvRect(x,y,0,0);
		}break;
		
		case CV_EVENT_LBUTTONUP:												//마우스때면 드로잉 종료 
		{
		DrawingBox=false;
			if(box.width<0)													//반대방향일경우 절댓값 
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

