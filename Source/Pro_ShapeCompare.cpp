//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "Pro_ShapeCompare.h"
#include <cv.h>
#include <opencv/highgui.h>
#include <KScOpenCvUtils.h>

// DLL�� ����� ���� �κ�
BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: break;
		case DLL_THREAD_ATTACH:  break;
		case DLL_THREAD_DETACH:  break;
		case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}

// �Լ��� ���� �κ�
/*int CDECL Pro_ShapeCompare(KScScalarImage2dUint8* src,KScScalarImage2dUint8* ref,double* result)*/
int CDECL Pro_ShapeCompare(KScScalarImage2dUint8* src,KScScalarImage2dUint8* ref,int* result)
{
// ��ó�� /////////////////////////////////////////////////////////////////////

    // �Է� ���� �ڷ� ���� �˻�.

    // ��� ���� �ڷ� ���� �˻�.

    // �Է� ���� �Ҵ� ���� �˻�.

	// ��� ���� �Ҵ� ���� �˻�.

// ���� ó�� �κ� /////////////////////////////////////////////////////////////

	char text;
	int count = 20;
	int dec, sign;
	double m_result[3];
	CvFont font;
	IplImage *src_img, *ref_img;
	cv::Mat m1 = KScScalarImage2dUint8ToMat(src);
	src_img = new IplImage(m1);
	cv::Mat m2 = KScScalarImage2dUint8ToMat(ref);
	ref_img = new IplImage(m2);

	// (1)3 ������ �������� ������ ��
	m_result[0] = cvMatchShapes (src_img, ref_img, CV_CONTOURS_MATCH_I1, 0);
	m_result[1] = cvMatchShapes (src_img, ref_img, CV_CONTOURS_MATCH_I2, 0);
	m_result[2] = cvMatchShapes (src_img, ref_img, CV_CONTOURS_MATCH_I3, 0);
	
	*result = (int)(m_result[0] * 100000);

// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.




