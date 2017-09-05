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
#include "Pro_Compare.h"
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
int CDECL Pro_Compare(KScScalarImage2dUint8* src,KScScalarImage2dUint8* ref,KScScalarImage2dUint8* dst,int* min_x,int* min_y,int* max_x,int* max_y)
{
// ��ó�� /////////////////////////////////////////////////////////////////////
	
    // �Է� ������ �ڷ� ���� �˻�.
    if (src->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}
	if (ref->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}

	// ��� ������ �ڷ� ���� �˻�.
    if (dst->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}

    // �Է� ������ �Ҵ� ���� �˻�.
	int dx = src->GetMainXSize();
	int dy = src->GetMainYSize();
    if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}
	int rdx = src->GetMainXSize();
	int rdy = src->GetMainYSize();
    if (!rdx || !rdy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"Pro_Compare", MB_OK);
        return FALSE;
	}

	// ��� ���۰� �Ҵ��� ���� �ʾҰų� �Է� ���ۿ� ũ�Ⱑ �ٸ� ���,
	// ��� ���۸� �Է� ���ۿ� ������ ũ��� ���Ҵ�.
	if (dx != dst->GetXSize() ||
		dy != dst->GetYSize())
	{
		// ROI�� �����Ǿ� ������ Free()���� ROI�� ������.
		dst->Free();
		// Alloc()�� ��ȯ�� : �������̸� 0, �����̸� 0�� �ƴ� ���� �ڵ�.
		if (dst->Alloc(dx, dy))
		{
			::MessageBox(NULL, "Fail to allocate output buffer.",
				"Pro_Compare", MB_OK);
			return FALSE;
		}
	}
	// ��� ������ ũ�Ⱑ �Է� ������ �Ͱ� ������ ���,
	else
	{
		// ����� ���۰� �ٸ� ���, 0���� �ʱ�ȭ.
		// �ʱ�ȭ�� ���� �ʰų� ����ڰ� ���ϴ� ������ �ʱ�ȭ�ص� ����.
		if (src != dst)
			dst->InitTo(0);
	}

// ���� ó�� �κ� /////////////////////////////////////////////////////////////
	
	double min_val, max_val;
	CvPoint min_loc, max_loc;
	CvSize dst_size;
	IplImage *src_img, *tmp_img, *dst_img;
	cv::Mat m1 = KScScalarImage2dUint8ToMat(src);
	src_img = new IplImage(m1);
	cv::Mat m2 = KScScalarImage2dUint8ToMat(ref);
	tmp_img = new IplImage(m2);
	
	// (1)Ž�� �̹��� ��ü�� ���ؼ�, ���ø��� ��Īġ(������ �������� ����)�� ���
	dst_size = cvSize (src_img->width - tmp_img->width + 1, src_img->height - tmp_img->height + 1);
	dst_img = cvCreateImage (dst_size, IPL_DEPTH_32F, 1);
	
	cvMatchTemplate (src_img, tmp_img, dst_img, CV_TM_CCOEFF_NORMED);
	cvMinMaxLoc (dst_img, &min_val, &max_val, &min_loc, &max_loc, NULL);
	
	// (2)���ø��� �����ϴ� ��ġ�� ������ �׸���
	
	cvRectangle (src_img, max_loc, cvPoint (max_loc.x + tmp_img->width, max_loc.y + tmp_img->height), CV_RGB(0, 0, 0), 3);
	cv::Mat ma(src_img);
	MatToKScScalarImage2dUint8(ma, dst);
	*min_x = max_loc.x;
	*min_y = max_loc.y;
	*max_x = max_loc.x + tmp_img->width;
	*max_y = max_loc.y + tmp_img->height;
	
// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.





