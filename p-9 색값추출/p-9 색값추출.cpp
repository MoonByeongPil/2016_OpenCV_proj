#include <highgui.h>

int main() 
{
	IplImage *image;	// 원본영상
	IplImage *color;		// 색 검출 영상

	int width, height;	// 창의 넓이, 높이
	int i, j, index,BR,BG;
	unsigned char R, G, B;

	CvCapture* capture = cvCaptureFromCAM(0);
	image = cvRetrieveFrame(capture);

	// image 에서 width와 height 정보를 가져온다.
	width = image->width;
	height = image->height;
	
	cvNamedWindow("Original",1);
	cvNamedWindow("Tracking",1);
	cvCreateTrackbar("B-R","Tracking",&BR,255,NULL);
	cvCreateTrackbar("B-G","Tracking",&BG,255,NULL);
///	cvResizeWindow("Original", width, height);
//	cvResizeWindow("Tracking", width, height);

	// image와 같은 크기를 갖는 3채널 영상 생성
	color = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);

	while(capture) {
		image = cvRetrieveFrame(capture);

		for(i = 0; i < (image->height); i++) 
		{
			for(j = 0; j < (image->widthStep); j += (image->nChannels)) 
			{
				index = i * image->widthStep + j;

				R = image->imageData[index+2];	// R영역
				G = image->imageData[index+1];	// 영역
				B = image->imageData[index+0];	// B영역

				// 붉은색으로 예상되는 범위 설정
				if(B-R > BR && B-G > BG ) {
					// 흰색으로
					color->imageData[(i*image->widthStep)+j + 0] = 255;	
					color->imageData[(i*image->widthStep)+j + 1] = 255;
					color->imageData[(i*image->widthStep)+j + 2] = 255;
				}
				else {
					// 검정색으로
					color->imageData[(i*image->widthStep)+j + 0] = 0;
					color->imageData[(i*image->widthStep)+j + 1] = 0;
					color->imageData[(i*image->widthStep)+j + 2] = 0;
				}
			}
		}

		cvShowImage("Original",image);
		cvShowImage("Tracking",color);

		if(cvWaitKey(33) >= 27)
			break;
	}
	cvReleaseCapture(&capture);
	cvReleaseImage(&color);
	cvDestroyWindow("Original");
	cvDestroyWindow("Tracking");

	return 0;
}
