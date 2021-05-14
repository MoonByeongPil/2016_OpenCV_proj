#include <cv.h>
#include <highgui.h>
#include <stdio.h>

CvRect box;																		//구조체 참조 선언 
bool DrawingBox = false;														//이벤트 논리변수 

void MouseCallBack(int event, int x, int y, int flags, void*param);				//마우스이벤트정의함수 선 정의 
void DrawBox(IplImage*img,CvRect rect);											//사각형그리기 박스 선 정의 

int main()
{
    IplImage* image = 0;								//이미지 구조체 포인터 변수선언 
	IplImage* resault = 0;
	
    CvCapture* capture = 0;  							//캡쳐 이미지 구조체 포인터 변수 선언  
	capture = cvCaptureFromCAM(0);						//capture에 0번 카메라 입력 연결을 선언 
	
	cvGrabFrame( capture );
	image = cvRetrieveFrame( capture,1 );
	
	box = cvRect(-1,-1,0,0);
	IplImage*temp = cvCloneImage(image);
	
	if( capture )										//캡쳐값이 존재할경우
	{
	
    	cvNamedWindow( "camera", 1 );					//윈도우 생성  
		cvNamedWindow("Box",1);

        cvSetMouseCallback("camera",MouseCallBack,(void*)image);	
        
		while(1)										
        {
            if( !cvGrabFrame( capture ))				//프레임이 드롭되면 프로그램 종료 
                break;

            image = cvRetrieveFrame( capture,1 );		//image에 capture에 받아온 단일 프레임을 저장 
            cvCopy(image,temp,0);
            
            if(DrawingBox)
			{	
				
				DrawBox(image,box);										//복사이미지에 드로잉 
				DrawBox(temp,box);
				resault=cvCreateImage(cvSize(box.width,box.height),IPL_DEPTH_32F,3);

				
				cvShowImage("Box",temp);
			}
			cvShowImage( "camera", image );				//image를 camera창에 표시  
			
		

            if(cvWaitKey(15)==27)break;
        }
        cvReleaseCapture( &capture );					//이미지 릴리스 
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
