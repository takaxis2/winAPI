#include <DirectXMath.h>
#include <iostream>
#include "DoubleBuffer.h"

using namespace std;
using namespace DirectX;



int main(void)
{

	//** �ּһ���� �˻���.
	if (!XMVerifyCPUSupport())
		cout << "�ּһ���� �˻���" << endl;









	CDoubleBuffer::GetInstance()->CreateBuffer();

	ULONGLONG Time = GetTickCount64();

	while (true)
	{
		if (Time + 500 < GetTickCount64())
		{
			Time = GetTickCount64();
			system("cls");


			CDoubleBuffer::GetInstance()->FlippingBuffer();
			CDoubleBuffer::GetInstance()->ClearBuffer();

			//** �Ʒ����� �ڵ� �ۼ�
			//CDoubleBuffer::GetInstance()->WriteBuffer();







			if (GetAsyncKeyState(VK_ESCAPE))
			{
				system("cls");
				break;
			}
		}
	}
	




	/*
	//** 2���� ������ ����ϴ� ����
	XMFLOAT2 Float2;

	Float2.x;
	Float2.y;

	//** 3���� ������ ����ϴ� ����
	XMFLOAT3 Float3;

	Float3.x;
	Float3.y;
	Float3.z;


	//** 4���� ������ ����ϴ� ����
	XMFLOAT4 Float4;

	Float4.x;
	Float4.y;
	Float4.z;
	Float4.w;
	*/


	//** 4���� ������ ���� �ϴ� �Լ�.
	XMVECTOR A = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR B = XMVectorSet(2.0f, 2.0f, 2.0f, 2.0f);
	XMVECTOR C = XMVectorSet(3.0f, 3.0f, 3.0f, 3.0f);
	XMVECTOR D = XMVectorSet(4.0f, 4.0f, 4.0f, 4.0f);



	//** XMVECTOR operator + 
	XMVECTOR N = A + B;
	
	//** XMVECTOR operator - 
	XMVECTOR U = A - B;

	//** XMVECTOR operator *  (��Į�� ��)
	XMVECTOR V = C * 10.0f;



	//** ������ 3���� ����
	XMFLOAT3 FloatN;
	XMFLOAT3 FloatU;
	XMFLOAT3 FloatV;
	

	//** ȿ�������� ����ϱ� ����. (SIMD)
	XMStoreFloat3(&FloatN, N);
	XMStoreFloat3(&FloatU, U);
	XMStoreFloat3(&FloatV, V);

	//** ���
	cout << "X : " << FloatN.x << "\tY : " << FloatN.y
		<< "\tZ : " << FloatN.z << endl;

	cout << "X : " << FloatU.x << "\tY : " << FloatU.y
		<< "\tZ : " << FloatU.z << endl;

	cout << "X : " << FloatV.x << "\tY : " << FloatV.y
		<< "\tZ : " << FloatV.z << endl;



	//** ������ ����ȭ
	XMFLOAT3 Float_n;
	XMVECTOR n = XMVector3Normalize(D);

	XMStoreFloat3(&Float_n, n);

	cout << "X : " << Float_n.x << "\tY : " << Float_n.y
		<< "\tZ : " << Float_n.z << endl;



	//** ����
	XMVECTOR u = XMVector3Dot(A, B);

	XMFLOAT3 Float_u;
	XMStoreFloat3(&Float_u, u);

	cout << "\n[����]" << endl;
	cout << "X : " << Float_u.x << "\tY : " << Float_u.y
		<< "\tZ : " << Float_u.z << endl;




	//** ����
	XMVECTOR v = XMVector3Cross(A, B);

	XMFLOAT3 Float_v;
	XMStoreFloat3(&Float_v, v);

	cout << "\n[����]" << endl;
	cout << "X : " << Float_v.x << "\tY : " << Float_v.y
		<< "\tZ : " << Float_v.z << endl;




	//** ������ ���̸� ����.
	XMVECTOR L = XMVector3Length(C);

	XMFLOAT3 FloatL;
	XMStoreFloat3(&FloatL, L);

	cout << "\n[����]" << endl;
	cout << "X : " << FloatL.x << "\tY : " << FloatL.y
		<< "\tZ : " << FloatL.z << endl;



	return 0;
}


/*
XMVectorZero : ��� ������ 0 �� ���͸� �����. (0 ���Ͷ�� ��)
XMVectorSplatOne : ��� ������ 1 �� ���͸� �����.
XMVectorSet : �־��� 4���� ���� �������� �ϴ� ���͸� �����.
XMVectorReplicate : �־��� ���� ��� ������ �Ǵ� ���͸� �����.
XMVectorSplatX, XMVectorSplatY, XMVectorSplatZ, XMVectorSplatW : ��� ������ �־��� ������ x, y, z, w �� �Ǵ� ���͸� �����.


XMVectorAbs : �־��� ������ ��� ������ ���밪�� ������ش�.
XMVectorCos, XMVectorSin, XMVectorTan : �־��� ���� ������ cos, sin, tan�� ����� �ش�.
XMVectorLog : �־��� ������ ���к��� �α׸� ����� �ش�. �α��� �ؼ��� 2 ��
XMVectorExp : �־��� ������ ���к��� ������ ����� �ش�. �������� 2 ��
XMVectorPow : �־��� ������ ���к� n ���� ����� �ش�. u.x ^ p.x, u.y ^ p.y....
XMVectorSqrt : �־��� ������ ���к� ��Ʈ�� ����� �ش�.
XMVectorSwizzile : ������ ���������� �����Ѵ�. (������ ���к� �ڸ� �ٲ�)
XMVectorMultiply : ������ ���к� ������ ����� �ش�.
XMVectorSaturate : ������ ������ 0 ~ 1.0 ������ ������ �����. (������ ����� ���� �߶� ������.)
XMVectorMin, XMVectorMax : ���� ���к��� ���ؼ� ������(ū ������) ���� ���ο� ���͸� ����� �ش�.

 ���� : ���� ��ȣ + �� �̿��Ѵ�.
 ���� : ���� ��ȣ - �� �̿��Ѵ�.
 ���� (�Ǽ��� ������ ����) : ������ȣ * �� �̿��Ѵ�.
 XMVector3Length : ������ ���̸� ���Ѵ�. (���� ���� x, y, z �� �����)
 XMVector3Normalize : ����(����) ���͸� ���Ѵ� (���� ���� x, y, z �� �����)
 XMVector3Dot : �� ������ ������ ���Ѵ�. (������ ������ ��Ʈ �����̶�� ��)
 XMVector3Cross : �� ������ ������ ���Ѵ�. (������ ������ ũ�ν� �����̶�� ��)
 XMVector3ComponentsFromNormal : ���⺤�͸� �������� �־��� ���͸� ���⺤�Ϳ� ������ ���Ϳ� ������ ���ͷ� ��������
 
 

 XMVector3Equal, XMVector3NotEqual : �� ���Ͱ� �������� �Ǵ�����
 XMVector3AngleBetweenVectors : �κ����� ������ ���� ������
 XMConvertToDegrees : ���Ȱ��� ��׸� (����)�� ��ȯ����
 XMConvertToRadians : ��׸�(����)�� �������� ��ȯ����
*/