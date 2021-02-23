#include <DirectXMath.h>
#include <iostream>
#include "DoubleBuffer.h"

using namespace std;
using namespace DirectX;



int main(void)
{

	//** 최소사양을 검사함.
	if (!XMVerifyCPUSupport())
		cout << "최소사양을 검사함" << endl;









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

			//** 아래부터 코드 작성
			//CDoubleBuffer::GetInstance()->WriteBuffer();







			if (GetAsyncKeyState(VK_ESCAPE))
			{
				system("cls");
				break;
			}
		}
	}
	




	/*
	//** 2개의 성분을 사용하는 벡터
	XMFLOAT2 Float2;

	Float2.x;
	Float2.y;

	//** 3개의 성분을 사용하는 벡터
	XMFLOAT3 Float3;

	Float3.x;
	Float3.y;
	Float3.z;


	//** 4개의 성분을 사용하는 벡터
	XMFLOAT4 Float4;

	Float4.x;
	Float4.y;
	Float4.z;
	Float4.w;
	*/


	//** 4개의 성분을 셋팅 하는 함수.
	XMVECTOR A = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR B = XMVectorSet(2.0f, 2.0f, 2.0f, 2.0f);
	XMVECTOR C = XMVectorSet(3.0f, 3.0f, 3.0f, 3.0f);
	XMVECTOR D = XMVectorSet(4.0f, 4.0f, 4.0f, 4.0f);



	//** XMVECTOR operator + 
	XMVECTOR N = A + B;
	
	//** XMVECTOR operator - 
	XMVECTOR U = A - B;

	//** XMVECTOR operator *  (스칼라 곱)
	XMVECTOR V = C * 10.0f;



	//** 성분이 3개인 벡터
	XMFLOAT3 FloatN;
	XMFLOAT3 FloatU;
	XMFLOAT3 FloatV;
	

	//** 효율적으로 사용하기 위함. (SIMD)
	XMStoreFloat3(&FloatN, N);
	XMStoreFloat3(&FloatU, U);
	XMStoreFloat3(&FloatV, V);

	//** 출력
	cout << "X : " << FloatN.x << "\tY : " << FloatN.y
		<< "\tZ : " << FloatN.z << endl;

	cout << "X : " << FloatU.x << "\tY : " << FloatU.y
		<< "\tZ : " << FloatU.z << endl;

	cout << "X : " << FloatV.x << "\tY : " << FloatV.y
		<< "\tZ : " << FloatV.z << endl;



	//** 벡터의 정규화
	XMFLOAT3 Float_n;
	XMVECTOR n = XMVector3Normalize(D);

	XMStoreFloat3(&Float_n, n);

	cout << "X : " << Float_n.x << "\tY : " << Float_n.y
		<< "\tZ : " << Float_n.z << endl;



	//** 내적
	XMVECTOR u = XMVector3Dot(A, B);

	XMFLOAT3 Float_u;
	XMStoreFloat3(&Float_u, u);

	cout << "\n[내적]" << endl;
	cout << "X : " << Float_u.x << "\tY : " << Float_u.y
		<< "\tZ : " << Float_u.z << endl;




	//** 외적
	XMVECTOR v = XMVector3Cross(A, B);

	XMFLOAT3 Float_v;
	XMStoreFloat3(&Float_v, v);

	cout << "\n[외적]" << endl;
	cout << "X : " << Float_v.x << "\tY : " << Float_v.y
		<< "\tZ : " << Float_v.z << endl;




	//** 벡터의 길이를 구함.
	XMVECTOR L = XMVector3Length(C);

	XMFLOAT3 FloatL;
	XMStoreFloat3(&FloatL, L);

	cout << "\n[길이]" << endl;
	cout << "X : " << FloatL.x << "\tY : " << FloatL.y
		<< "\tZ : " << FloatL.z << endl;



	return 0;
}


/*
XMVectorZero : 모든 성분이 0 임 벡터를 만든다. (0 벡터라고 함)
XMVectorSplatOne : 모든 성분이 1 인 벡터를 만든다.
XMVectorSet : 주어진 4개의 값을 성분으로 하는 벡터를 만든다.
XMVectorReplicate : 주어진 값이 모든 성분이 되는 벡터를 만든다.
XMVectorSplatX, XMVectorSplatY, XMVectorSplatZ, XMVectorSplatW : 모든 성분이 주어진 벡터의 x, y, z, w 가 되는 벡터를 만든다.


XMVectorAbs : 주어진 벡터의 모든 성분의 절대값을 계산해준다.
XMVectorCos, XMVectorSin, XMVectorTan : 주어진 벡터 성분의 cos, sin, tan를 계산해 준다.
XMVectorLog : 주어진 벡터의 성분별로 로그를 계산해 준다. 로그의 밑수는 2 임
XMVectorExp : 주어진 벡터의 성분별로 지수를 계산해 준다. 지수값은 2 임
XMVectorPow : 주어진 베터의 성분별 n 승을 계산해 준다. u.x ^ p.x, u.y ^ p.y....
XMVectorSqrt : 주어진 벡터의 성분별 루트를 계산해 준다.
XMVectorSwizzile : 벡터의 스위질링을 수행한다. (벡터의 성분별 자리 바꿈)
XMVectorMultiply : 벡터의 성분별 곱셈을 계산해 준다.
XMVectorSaturate : 벡터의 성분을 0 ~ 1.0 사이의 값으로 만든다. (범위를 벗어나면 값을 잘라 버린다.)
XMVectorMin, XMVectorMax : 벡터 성분별로 비교해서 작은값(큰 값으로) 으로 새로운 벡터를 만들어 준다.

 덧셈 : 덧셈 기호 + 를 이용한다.
 뺄셈 : 뺄셈 기호 - 를 이용한다.
 곱셈 (실수와 벡터의 곱셈) : 곱셈기호 * 를 이용한다.
 XMVector3Length : 벡터의 길이를 구한다. (벡터 성분 x, y, z 만 사용함)
 XMVector3Normalize : 방향(단위) 벡터를 구한다 (벡터 성분 x, y, z 만 사용함)
 XMVector3Dot : 두 벡터의 내적을 구한다. (벡터의 내적을 도트 연산이라고 함)
 XMVector3Cross : 두 벡터의 외적을 구한다. (벡터의 외적을 크로스 연산이라고 함)
 XMVector3ComponentsFromNormal : 방향벡터를 기준으로 주어진 벡터를 방향벡터에 평행인 벡터와 수직인 벡터로 나누어줌
 
 

 XMVector3Equal, XMVector3NotEqual : 두 벡터가 같은지를 판단해줌
 XMVector3AngleBetweenVectors : 두벡터의 사이의 각을 구해줌
 XMConvertToDegrees : 라디안값을 디그리 (각도)로 변환해줌
 XMConvertToRadians : 디그리(각도)를 라디안으로 변환해줌
*/