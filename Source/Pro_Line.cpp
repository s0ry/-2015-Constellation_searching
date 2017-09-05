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
#include "Pro_Line.h"
#include <cv.h>
#include <highgui.h>
#include <KScOpenCVUtils.h>

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
int CDECL Pro_Line(KScScalarImage2dUint8* src,KScScalarImage2dUint8* dst)
{
// ��ó�� /////////////////////////////////////////////////////////////////////
	
    // �Է� ������ �ڷ� ���� �˻�.
    if (src->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Input buffer type not suitable.",
			"Pro_LookupTable", MB_OK);
        return FALSE;
	}

	// ��� ������ �ڷ� ���� �˻�.
    if (dst->GetId() != KS_SCALAR_IMAGE_2D_UINT8)
	{
		::MessageBox(NULL, "Output buffer type not suitable.",
			"Pro_LookupTable", MB_OK);
        return FALSE;
	}

    // �Է� ������ �Ҵ� ���� �˻�.
	int dx = src->GetMainXSize();
	int dy = src->GetMainYSize();
    if (!dx || !dy)
	{
		::MessageBox(NULL, "Input buffer not allocated.",
			"Pro_LookupTable", MB_OK);
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
				"Pro_LookupTable", MB_OK);
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

	// ���۸� 2�������� �����ϱ� ���� ó��
	KSdUint8 **pSourceArray      = src->Get2dArray();
	KSdUint8 **pDestinationArray = dst->Get2dArray();

	double X[200];
	double Y[200];
	register int index = 0;
	register int x = dx - 1, y = dy - 1;

	for (register int i = 1, j ; i < y ; i++){
		for (j = 1 ; j < x ; j++){
			if (pSourceArray[i][j] == 0){
				X[index] = j;
				Y[index] = i;
				index++;
			}
		}
	}
	
	
	cv::Mat m;
	m = KScScalarImage2dUint8ToMat(src);
	
	register double distance;

	for (register int a=0,b ; a<index ; a++){
		for (b=0 ; b<index ; b++){
			distance = sqrt((X[a]-X[b])*(X[a]-X[b]) + (Y[a]-Y[b])*(Y[a]-Y[b]));
			if (distance < 100){
				cv::line(m, cvPoint (X[a], Y[a]), cvPoint (X[b], Y[b]), cvScalar(0, 0, 0), 1, 8, 0);
			}
		}
	}

	MatToKScScalarImage2dUint8(m, dst);
	
	// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.




