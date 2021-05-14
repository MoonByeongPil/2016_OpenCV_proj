#include <cv.h>
#include <highgui.h>


// ������ ���� �� ��
void ucvViewImage(char *WindowNmae, IplImage *image)
{
	cvNamedWindow( WindowName, 1);
	cvShowImage( WindowName, image );
}

int main()
{
	double min, max;
	CvPoint left_top;

	IplImage *A = cvLoadImage("My_Desk.jpg", -1);	// å��(A)�� ���� �а�
	IplImage *B = cvLoadImage("Stapler.jpg", -1);	// �������÷�(B)�� �д´�.
	IplImage* C = cvCreateImage( cvSize( A->width - B->width+1, A->height - B->height+1 ), IPL_DEPTH_32F, 1 );	// �������� ���� �̹���(C)

	cvMatchTemplate(A, B, C, CV_TM_CCOEFF_NORMED);	// �������� ���Ͽ� C �� �׸���.
	cvMinMaxLoc(C, &min, &max, NULL, &left_top,0);	// �������� �ִ밪�� ���� ��ġ ã�� 
	cvRectangle(A, left_top, cvPoint(left_top.x + B->width, left_top.y + B->height), CV_RGB(255,0,0),0,0,0);	// ã�� ��ü�� ������� �׸���.

	ucvViewImage("result",A);	// ��� ����
	ucvViewImage("sample",B);	// �������÷�(B) ����
	ucvViewImage("C",C);			// ������ �̹��� ����

	cvWaitKey(0);
		

	// ��� �̹��� ������
	cvReleaseImage(&A);
	cvReleaseImage(&B);
	cvReleaseImage(&C);

	// ��� ������ ����
	cvDestroyAllWindows();
}
