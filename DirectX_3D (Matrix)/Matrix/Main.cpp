#include <iostream>
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;



void Output(const XMMATRIX& _m)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			cout << _m.r[i].m128_f32[j] << "\t";
		cout << endl;
	}
	cout << endl;
}



int main(void)
{

	//** ��� A�� ����
	XMMATRIX A( 1.0f, 3.0f, 5.0f, 7.0f,
				9.0f, 1.0f, 3.0f, 5.0f,
				1.0f, 3.0f, 5.0f, 1.0f,
				3.0f, 5.0f, 7.0f, 9.0f);
	
	//** ��� B�� ����
	XMMATRIX B( 2.0f, 6.0f, 6.0f, 4.0f,
				8.0f, 4.0f, 4.0f, 8.0f,
				6.0f, 2.0f, 6.0f, 6.0f,
				8.0f, 4.0f, 2.0f, 8.0f);



	//** ����� ����
	XMMATRIX C = A * B;
	Output(C);


	//** ����� ����
	XMMATRIX D = A + B;
	Output(D);
	


	//** ����� �E��
	XMMATRIX E = A - B;
	Output(E);


	//**  A + (B + C)  =  (A + B) + C
	XMMATRIX F = A + (B + C);
	XMMATRIX G = (A + B) + C;

	Output(F);
	Output(G);




	//** ����� ���� = XMMatrixMultiply( _t, _d)
	Output( XMMatrixMultiply(A, B));


	//** ������� = XMMatrixIdentity()
	Output(XMMatrixIdentity());



	//** ��ġ ��� = XMMatrixTranspose(_m)
	Output(XMMatrixTranspose(G));



	//** ����� �E��
	XMMATRIX H = A * 2;
	Output(H);



	return 0;
}