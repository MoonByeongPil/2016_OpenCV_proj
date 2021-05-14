#include <cv.h>
#include <highgui.h>
#include <stdio.h> 

int main()
{ 
	int thresholdS=190;															//���ð� ������ �߾Ӱ� ���� 
	int threshold=190;
	
	double min, max;															//�������� �ִ��ּҰ����� 
	CvPoint left_top;															//���� ��ġ���� 
	
    IplImage* imageO = 0;														//�̹��� ����ü ������ ���� ���� 
    IplImage* imageG = 0;
    IplImage* imageH = 0;
    IplImage* imageR = 0;
    	
	IplImage* imageS = 0;
	IplImage* imageSG = 0;
	IplImage* imageSH = 0;
	
	IplImage* imageC = 0;
	
	
	CvCapture*capture=0;														//ī�޶�� ���� 
	capture=cvCaptureFromCAM(0);

	
	cvNamedWindow( "Original", 0 );												//��������� 
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
	
	
	cvCreateTrackbar("threshold","threshold",&threshold,255,NULL);				//�����̴� ���� 
	cvCreateTrackbar("thresholdS","thresholdS",&thresholdS,255,NULL);
	
	
	cvGrabFrame( capture );														//ī�޶� ���� 
	imageO = cvRetrieveFrame( capture,1 );										//�̹��� ���� 
	imageS = cvLoadImage("p-3_tamplet.jpg", -1);
	cvShowImage("sample",imageS);	
										 
	
	
	while(1)
	{	
		if(cvWaitKey(15)==27)break;
		if( !cvGrabFrame( capture ))break;		
		
		if(!imageR)																//����̹����� ������(ó��) �̹��� ���� 
		{				
				imageSG=cvCreateImage(cvGetSize(imageS),IPL_DEPTH_8U,1);		
				imageSH=cvCreateImage(cvGetSize(imageS),IPL_DEPTH_8U,1);
				
				imageR = cvCloneImage(imageO);
				imageG=cvCreateImage(cvGetSize(imageO),IPL_DEPTH_8U,1);
				imageH=cvCreateImage(cvGetSize(imageO),IPL_DEPTH_8U,1);
				
				imageC = cvCreateImage( cvSize( imageO->width - imageS->width+1, imageO->height - imageS->height+1 ), IPL_DEPTH_32F, 1 );
				
		}
		cvGrabFrame( capture );													//�̹��� ǥ�� 
		
		imageO = cvRetrieveFrame( capture,1 );
		cvCopy(imageO,imageR,0);  
		
		cvCvtColor(imageO, imageG, CV_RGB2GRAY);								//�̹��� ����ȭ 
		cvThreshold(imageG,imageH,threshold,255,CV_THRESH_BINARY);
		
		cvCvtColor(imageS, imageSG, CV_RGB2GRAY);
		cvThreshold(imageSG,imageSH,thresholdS,255,CV_THRESH_BINARY);			//���� ����ȭ 
				
		
		cvMatchTemplate(imageH, imageSH, imageC, CV_TM_CCOEFF_NORMED);			//������ ��Ī 
			
		cvMinMaxLoc(imageC, &min, &max, NULL, &left_top,0);						//�ִ��ּ� ���
		printf("max:%f min:%f\r",max,min);	
		cvRectangle(imageR, left_top, cvPoint(left_top.x + imageS->width, left_top.y + imageS->height), CV_RGB(255,0,0),5,0,0);	//�ش���ġ�� �簢�� ���
		 
						 
		cvShowImage("sampleH",imageSH);											//��� ���
		cvShowImage("Original",imageO);	
		cvShowImage("Output",imageH);
		cvShowImage("C",imageC);
		cvShowImage("Result",imageR);			
		
	}


	cvReleaseCapture( &capture );												//�̹���,����,������ ������ 
	
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
