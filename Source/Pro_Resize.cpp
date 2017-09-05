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
#include "Pro_Resize.h"
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
int CDECL Pro_Resize(KScScalarImage2dUint8* src,KScScalarImage2dUint8* dst)
{
// ��ó�� /////////////////////////////////////////////////////////////////////

    // �Է� ������ �ڷ� ���� �˻�.
    if (src->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input pSourceBuffer type not suitable.",
			"Pro_Resize", MB_OK);
        return FALSE;
	}

    // ��� ������ �ڷ� ���� �˻�.
    if (dst->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Output pSourceBuffer type not suitable.",
			"Pro_Resize", MB_OK);
        return FALSE;
	}

    // �Է� ������ �Ҵ� ���� �˻�.
	int dx = src->GetMainXSize();
	int dy = src->GetMainYSize();
    if (!dx || !dy)
	{
		::MessageBox(NULL, "Input pSourceBuffer not allocated.",
			"Pro_Resize", MB_OK);
        return FALSE;
	}

 	// �Է� ���۸� �������� ���� ó�� ���� ����.
	dx = src->GetXSize();
	dy = src->GetYSize();

	// ROI�� �����Ǿ� ������ Free()���� ROI�� ������.
	dst->Free();
	if (dst->Alloc(dx, dy))
	{
		::MessageBox(NULL, "Fail to allocate output buffer.",
			"Pro_Resize", MB_OK);
		return FALSE;
	}

// ���� ó�� �κ� /////////////////////////////////////////////////////////////

	// ���۸� 1���� �迭�� ����.
	KSdUint8 **pSourceArray      = src->Get2dArray();
	KSdUint8 **pDestinationArray = dst->Get2dArray();

	int buf_size = dx * dy;
	int min_x = dx, min_y = dy, max_x, max_y;

	for (register int i=0,j ; i<dy ; i++){
		for (j=0 ; j<dx ; j++){
			pDestinationArray[i][j] = pSourceArray[i][j];
			if (pSourceArray[i][j] != 0 && min_x > j){
				min_x = j;
			}
			if (pSourceArray[i][j] != 0 && min_y > i){
				min_y = i;
			}
			if (pSourceArray[i][j] != 0){
				max_x = j;
				max_y = i;
			}
		}
	}
	
	IplImage *src_img, *dst_img;
	cv::Mat m1 = KScScalarImage2dUint8ToMat(src);
	src_img = new IplImage(m1);
	cv::Mat m2 = KScScalarImage2dUint8ToMat(dst);
	dst_img = new IplImage(m2);

	cvSetImageROI(src_img, cvRect(min_x, min_y, (max_x - min_x), (max_y - min_y))); 
	dst_img = (IplImage*)cvClone(src_img);

	cv::Mat ma(dst_img);
	MatToKScScalarImage2dUint8(ma, dst);
	
// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.




