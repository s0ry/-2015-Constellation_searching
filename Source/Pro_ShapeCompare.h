//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// KSClass ���̺귯���� ��ũ
//
//////////////////////////////////////////////////////////////////////////
//
// ��� ���ϰ� ���̺귯�� ���� �˻��� ���Ͽ�
// Visual Studio���� �޴� Tools - Options - Directories �ǿ���
// Show Directories for: �κ���
//     Include files���� KSClass�� Include�� ���丮��
//     Library files���� KSClass�� Lib       ���丮�� �����Ͽ��� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////////
//
// * ������
//
// Show Directories for: �κ���
//     Include files�� KSClass�� Include�� Lib ���丮�� ��� ������ ���,
//     ��ũ ���� �߻��Ѵ�.
//
//////////////////////////////////////////////////////////////////////////

#include "KSClass.h" // KSClass�鿡 ���� ���

// DLL �ܺο��� ȣ���ϱ� ���ؼ� �ʿ��� �κ� ...
extern "C" __declspec( dllexport )
/*int CDECL Pro_ShapeCompare(KScScalarImage2dUint8* src,KScScalarImage2dUint8* ref,KScScalarImage2dUint8* dst)*/
/*int CDECL Pro_ShapeCompare(KScScalarImage2dUint8* src,KScScalarImage2dUint8* ref,double* result)*/
int CDECL Pro_ShapeCompare(KScScalarImage2dUint8* par0,KScScalarImage2dUint8* par1,int* par2);

// 2 �� �̻��� �Լ��� export �� ���, �Ʒ��� �������� �����մϴ�.




