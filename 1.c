#include <cv.h>
#include <highgui.h>


void ucvViewCam(IplImage*image, CvCapture* capture, char *WindowName);
void ucvViewImage(char *WindowName, IplImage *image)
{
	cvNamedWindow( WindowName, 0);
	cvShowImage( WindowName, image );
}
int main()
{
	unsigned char R,B,G,D;	
	
	int x,y;
	int index;	
	int bins = 256;                               //
	int sizes[] = {bins};                         //
		
	float max_value = 0, min_value = 0;	
	
	float MR,MB,MG,M;
	
	float xranges[] = {0, 64};						//
	float*ranges[] = {xranges};						//히스토그램 선언 활용 
	
	IplImage*image,*imageR,*imageG,*imageB,*sampleR,*sampleG,*sampleB,*sample,*result;       //IplImage(변수 형태float같은)로 이미지를 선언한다.  (Image=영상)이라는 것 기억/   *는 포인터 변수 선언  
		
	CvHistogram*ShistR = cvCreateHist( 1, sizes, CV_HIST_ARRAY, ranges, 1),     // 히스토그램을 선언하는 변수=>함수  
			   *ShistB = cvCreateHist( 1, sizes, CV_HIST_ARRAY, ranges, 1),
			   *ShistG = cvCreateHist( 1, sizes, CV_HIST_ARRAY, ranges, 1),
			   *IhistR = cvCreateHist( 1, sizes, CV_HIST_ARRAY, ranges, 1),
			   *IhistB = cvCreateHist( 1, sizes, CV_HIST_ARRAY, ranges, 1),
			   *IhistG = cvCreateHist( 1, sizes, CV_HIST_ARRAY, ranges, 1);
		
	CvCapture* capture;  							//
	capture = cvCaptureFromCAM(0);					//카메라 사용 정의 (0번)	
	
	image = cvRetrieveFrame( capture,1 );
	imageR=cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	imageB=cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	imageG=cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	
	result=cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 3);
	
	sample=cvLoadImage("p-3_tamplet.jpg",-1);
	sampleR=cvCreateImage(cvSize(sample->width, sample->height), IPL_DEPTH_8U, 1);
	sampleB=cvCreateImage(cvSize(sample->width, sample->height), IPL_DEPTH_8U, 1);
	sampleG=cvCreateImage(cvSize(sample->width, sample->height), IPL_DEPTH_8U, 1);
	
	cvSplit(sample,sampleB,sampleR,sampleG,NULL);
	
	cvCalcHist(&sampleR,ShistR,0,0);
	cvCalcHist(&sampleG,ShistB,0,0);
	cvCalcHist(&sampleB,ShistG,0,0);
	
	ucvViewImage("R",sampleR);
	ucvViewImage("B",sampleB);
	ucvViewImage("G",sampleG);
	
	cvNamedWindow( "camera",0);

	
	while(1)
	{
		ucvViewCam(image,capture,"camera");
		
		cvSplit(image,imageB,imageR,imageG,NULL);
		
		cvCalcHist(&imageR,IhistR,0,0);
		cvCalcHist(&imageG,IhistB,0,0);
		cvCalcHist(&imageB,IhistG,0,0);
		
		for(y = 0; y < (image->height); y+=9) 
		{			
			for(x = 0; x < (image->widthStep); x += 9) 
			{
				index = y * image->widthStep + x*3;
				
				B = image->imageData[index+2];	
				G = image->imageData[index+1];	
				R = image->imageData[index+0];	
				
				MR= cvGetReal1D( ShistR->bins,R )/cvGetReal1D( IhistR->bins,R);
				MB= cvGetReal1D( ShistB->bins,B )/cvGetReal1D( IhistR->bins,B);
				MG= cvGetReal1D( ShistG->bins,G )/cvGetReal1D( IhistG->bins,G);
				
/*				M = (cvGetReal1D( ShistR->bins,R )+cvGetReal1D( ShistB->bins,B )+cvGetReal1D( ShistG->bins,G ))/
					(cvGetReal1D( IhistR->bins,R)+cvGetReal1D( IhistR->bins,B)+cvGetReal1D( IhistG->bins,G));
				
				D=M/3*256;*/
				D=(MR+MG+MB)*256;
				result->imageData[index+0] = D;	
				result->imageData[index+1] = D;
				result->imageData[index+2] = D;
			}
		}
		
		ucvViewImage("result",result);
		
		if( cvWaitKey(10) >= 0 )
            break;
	}
    cvReleaseCapture( &capture );					//이미지 릴리스 
	cvReleaseImage( &image );						
    cvDestroyAllWindows();
	
}

void ucvViewCam(IplImage*image, CvCapture* capture, char *WindowName)
{
	if( capture )										//캡쳐값이 존재할경우 
	{    					
        image = cvRetrieveFrame( capture,1 );		//image에 capture에 받아온 단일 프레임을 저장 
		cvShowImage( WindowName, image );				//image를 camera창에 표시  		     
    }
}

