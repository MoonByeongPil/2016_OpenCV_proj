#include <cv.h>
#include <highgui.h>
#include <stdio.h> 

int main()
{ 
	int thresholdS=190;															//샘플과 비디오의 중앙값 선언 
	int threshold=190;
	
	double min, max;															//상관계수의 최대최소값선언 
	CvPoint left_top;															//기준 위치선언 
	
    IplImage* imageO = 0;														//이미지 구조체 포인터 변수 선언 
    IplImage* imageG = 0;
    IplImage* imageH = 0;
    IplImage* imageR = 0;
    	
	IplImage* imageS = 0;
	IplImage* imageSG = 0;
	IplImage* imageSH = 0;
	
	IplImage* imageC = 0;
	
	
	CvCapture*capture=0;														//카메라와 연결 
	capture=cvCaptureFromCAM(0);

	
	cvNamedWindow( "Original", 0 );												//윈도우생성 
	cvResizeWindow( "Original", 320,240 );
    
    cvNamedWindow( "Output", 0 );
	cvResizeWindow( "Output", 320,240 );
	
	cvNamedWindow( "Result", 0 );
	cvResizeWindow( "Result", 320,240 );
	
	cvNamedWindow( "C", 0 );
	cvResizeWindow( "C", 320,240 );
	
	cvNamedWindow( "sample", 0 );
	cvResizeWindow( "sample", 320,240 );
	
	cvNamedWindow( "sampleH", 0 );
	cvResizeWindow( "sampleH", 320,240 );
	
	cvNamedWindow( "threshold", 0 );
	cvResizeWindow( "threshold", 640,100 );
	
	cvNamedWindow( "thresholdS", 0 );
	cvResizeWindow( "thresholdS",640,100 );
	
	
	cvCreateTrackbar("threshold","threshold",&threshold,255,NULL);				//슬라이더 생성 
	cvCreateTrackbar("thresholdS","thresholdS",&thresholdS,255,NULL);
	
	
	cvGrabFrame( capture );														//카메라 연결 
	imageO = cvRetrieveFrame( capture,1 );										//이미지 정의 
	imageS = cvLoadImage("p-3_tamplet.jpg", -1);
	cvShowImage("sample",imageS);	
										 
	
	
	while(1)
	{	
		if(cvWaitKey(15)==27)break;
		if( !cvGrabFrame( capture ))break;		
		
		if(!imageR)																//결과이미지가 없을때(처음) 이미지 생성 
		{				
				imageSG=cvCreateImage(cvGetSize(imageS),IPL_DEPTH_8U,1);		
				imageSH=cvCreateImage(cvGetSize(imageS),IPL_DEPTH_8U,1);
				
				imageR = cvCloneImage(imageO);
				imageG=cvCreateImage(cvGetSize(imageO),IPL_DEPTH_8U,1);
				imageH=cvCreateImage(cvGetSize(imageO),IPL_DEPTH_8U,1);
				
				imageC = cvCreateImage( cvSize( imageO->width - imageS->width+1, imageO->height - imageS->height+1 ), IPL_DEPTH_32F, 1 );
				
		}
		cvGrabFrame( capture );													//이미지 표시 
		
		imageO = cvRetrieveFrame( capture,1 );
		cvCopy(imageO,imageR,0);  
		
		cvCvtColor(imageO, imageG, CV_RGB2GRAY);								//이미지 이진화 
		cvThreshold(imageG,imageH,threshold,255,CV_THRESH_BINARY);
		
		cvCvtColor(imageS, imageSG, CV_RGB2GRAY);
		cvThreshold(imageSG,imageSH,thresholdS,255,CV_THRESH_BINARY);			//샘플 이진화 
				
		
		cvMatchTemplate(imageH, imageSH, imageC, CV_TM_CCOEFF_NORMED);			//상관계수 매칭 
			
		cvMinMaxLoc(imageC, &min, &max, NULL, &left_top,0);						//최대최소 출력
		printf("max:%f min:%f\r",max,min);	
		cvRectangle(imageR, left_top, cvPoint(left_top.x + imageS->width, left_top.y + imageS->height), CV_RGB(255,0,0),5,0,0);	//해당위치에 사각형 출력
		 
						 
		cvShowImage("sampleH",imageSH);											//결과 출력
		cvShowImage("Original",imageO);	
		cvShowImage("Output",imageH);
		cvShowImage("C",imageC);
		cvShowImage("Result",imageR);			
		
	}


	cvReleaseCapture( &capture );												//이미지,연결,윈도우 릴리즈 
	
	cvReleaseImage(&imageO);
	cvReleaseImage(&imageG);
	cvReleaseImage(&imageR);
	cvReleaseImage(&imageH);
	cvReleaseImage(&imageS);
	cvReleaseImage(&imageSG);
	cvReleaseImage(&imageSH);
	cvReleaseImage(&imageC);


	cvDestroyAllWindows();
}
