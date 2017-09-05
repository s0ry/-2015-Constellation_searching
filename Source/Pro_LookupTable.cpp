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
#include "Pro_LookupTable.h"

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
int CDECL Pro_LookupTable(KScScalarImage2dUint8* src,KScScalarImage2dUint8* dst)
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
    KSdUint8 *pSourceArray      = src->GetBuffer();
    KSdUint8 *pDestinationArray = dst->GetBuffer();

	int bufSize = dx * dy;

	// ������׷� ���� look up table�� ���� ������ ����
	unsigned char lut[256];

	// ������׷� ������ �ʱ�ȭ
	for (register int i = 0 ; i < 256 ; i++){
		if (i < 50)
			lut[i] = 255;
		else
			lut[i] = 0;
	}

	// ����� Lookup table�� ���Ͽ� �Է¿����� ������� ���
	for (int i = 0 ; i < bufSize ; i++)
		pDestinationArray[i] = lut[pSourceArray[i]];

// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.



