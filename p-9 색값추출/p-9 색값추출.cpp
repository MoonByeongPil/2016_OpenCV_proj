#include <highgui.h>

int main() 
{
	IplImage *image;	// ��������
	IplImage *color;		// �� ���� ����

	int width, height;	// â�� ����, ����
	int i, j, index,BR,BG;
	unsigned char R, G, B;

	CvCapture* capture = cvCaptureFromCAM(0);
	image = cvRetrieveFrame(capture);

	// image ���� width�� height ������ �����´�.
	width = image->width;
	height = image->height;
	
	cvNamedWindow("Original",1);
	cvNamedWindow("Tracking",1);
	cvCreateTrackbar("B-R","Tracking",&BR,255,NULL);
	cvCreateTrackbar("B-G","Tracking",&BG,255,NULL);
///	cvResizeWindow("Original", width, height);
//	cvResizeWindow("Tracking", width, height);

	// image�� ���� ũ�⸦ ���� 3ä�� ���� ����
	color = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);

	while(capture) {
		image = cvRetrieveFrame(capture);

		for(i = 0; i < (image->height); i++) 
		{
			for(j = 0; j < (image->widthStep); j += (image->nChannels)) 
			{
				index = i * image->widthStep + j;

				R = image->imageData[index+2];	// R����
				G = image->imageData[index+1];	// ����
				B = image->imageData[index+0];	// B����

				// ���������� ����Ǵ� ���� ����
				if(B-R > BR && B-G > BG ) {
					// �������
					color->imageData[(i*image->widthStep)+j + 0] = 255;	
					color->imageData[(i*image->widthStep)+j + 1] = 255;
					color->imageData[(i*image->widthStep)+j + 2] = 255;
				}
				else {
					// ����������
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
