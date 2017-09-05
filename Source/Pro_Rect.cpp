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
#include "Pro_Rect.h"
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
int CDECL Pro_Rect(int* min_x,int* min_y,int* max_x,int* max_y,KScRgbImage2d* src,KScRgbImage2d* dst)
{
// ��ó�� /////////////////////////////////////////////////////////////////////

    // �Է� ���� �ڷ� ���� �˻�.
	if(src->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Input buffer type not suitable.", "Pro_Rect", MB_OK);
		return FALSE;
	}
	
	// ��� ���� �ڷ� ���� �˻�.
	if(dst->GetId() != KS_RGB_IMAGE_2D)
	{
		::MessageBox(NULL, "Output buffer type not suitable.", "Pro_Rect", MB_OK);
		return FALSE;
	}

	// �Է� ���� �Ҵ� ���� �˻�.
	int dx = src->GetMainXSize();
	int dy = src->GetMainYSize();

	// ��� ���� �Ҵ� ���� �˻�.
	if(dx != dst->GetMainXSize() || dy != dst->GetMainYSize())
	{
		dst->Free();
		dst->Alloc(dx, dy);
	}
	dst->InitTo(0);

// ���� ó�� �κ� /////////////////////////////////////////////////////////////

	KSdUint8 **pSrouceArray_R = src->GetRed2dArray();
	KSdUint8 **pSrouceArray_G = src->GetGreen2dArray();
	KSdUint8 **pSrouceArray_B = src->GetBlue2dArray();
	KSdUint8 **pDestinationArray_R = dst->GetRed2dArray();
	KSdUint8 **pDestinationArray_G = dst->GetGreen2dArray();
	KSdUint8 **pDestinationArray_B = dst->GetBlue2dArray();
	
	for (register int i=0,j ; i<dy ; i++){
		for (j=0 ; j<dx ; j++){
			pDestinationArray_R[i][j] = pSrouceArray_R[i][j];
			pDestinationArray_G[i][j] = pSrouceArray_G[i][j];
			pDestinationArray_B[i][j] = pSrouceArray_B[i][j];
		}
	}
	
	CvPoint pt1, pt2;
	pt1.x = *min_x;
	pt1.y = *min_y;
	pt2.x = *max_x;
	pt2.y = *max_y;

	cv::Mat m1 = KScRgbImage2dToMat(dst);
	cv::rectangle (m1, pt1, pt2, CV_RGB(255, 0, 0), 3);
	MatToKScRgbImage2d(m1,dst);

// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


