#include <cv.h>
#include <highgui.h>
#include <stdio.h>

int main() 
{
	IplImage *image,														// 원본영상
			 *color,															// 색 검출 영상
			 *temp;
			 	
	int y, x, index,
		BR=21,BG=21,Bc=170,	
		centerX=150,centerY=150,
		size=65,sigmaX=0,sigmaY=0,
		numberX=0,numberY=0;
		
	unsigned char R, G, B;
	
	CvCapture* capture = cvCaptureFromCAM(0);
	
	CvPoint left_top;
	
	image = cvRetrieveFrame(capture,0);
	color = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	temp = cvCloneImage(color);
	
	cvNamedWindow("Original",1);
	cvNamedWindow("Tracking",1);
	cvCreateTrackbar("B-R","Tracking",&BR,255,NULL);
	cvCreateTrackbar("B-G","Tracking",&BG,255,NULL);
	cvCreateTrackbar("Bc","Tracking",&Bc,255,NULL);
	cvCreateTrackbar("size","Tracking",&size,100,NULL);					
	
	while(capture) 
	{
		sigmaX=0;
		sigmaY=0;
		numberX=0;
		numberY=0;
		
		image = cvRetrieveFrame(capture,0);
		
		for(y = 0; y < (image->height); y+=3) 
		{			
			for(x = 0; x < (image->widthStep); x += 3) 
			{
				index = y * image->widthStep + x*3;
				
				R = image->imageData[index+2];	
				G = image->imageData[index+1];	
				B = image->imageData[index+0];	
				
				if(image)
				{
					if(B-R > BR && B-G > BG && B > Bc) 
					{
						color->imageData[index+0] = 255;	
						color->imageData[index+1] = 255;
						color->imageData[index+2] = 255;
						
						if(centerX-size<x&&x<centerX+size&&centerY-size<y&&y<centerY+size)
						{
							if((centerX-x)^2<size)	sigmaX=sigmaX+x;						
							if((centerX-y)^2<size)	sigmaY=sigmaY+y;
								
							numberX=numberX+1;      
							numberY=numberY+1;							
						}									
					}
					else 
					{
						color->imageData[index+0] = 0;
						color->imageData[index+1] = 0;
						color->imageData[index+2] = 0;
					}
				}
			}
		}		
		
		if(numberX>0&&numberY>0)
		{	
			centerX=sigmaX/numberX;
			centerY=sigmaY/numberY;
		}	

		cvCopy(color,temp,0);	
		cvRectangle(temp, cvPoint(centerX-size,centerY-size),cvPoint(centerX+size, centerY+size), CV_RGB(255,0,0),5,0,0);
		cvRectangle(image, cvPoint(centerX-size,centerY-size),cvPoint(centerX+size, centerY+size), CV_RGB(255,0,0),5,0,0);

		
		cvShowImage("Original",image);
		cvShowImage("Tracking",temp);
		
		if(cvWaitKey(33) >= 27)	break;
	}
	cvReleaseCapture(&capture);
	cvReleaseImage(&image);
	cvReleaseImage(&temp);
	cvReleaseImage(&color);
	cvDestroyAllWindows();

	return 0;
}
