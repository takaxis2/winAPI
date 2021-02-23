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

	//** Çà·Ä AÀÇ Á¤ÀÇ
	XMMATRIX A( 1.0f, 3.0f, 5.0f, 7.0f,
				9.0f, 1.0f, 3.0f, 5.0f,
				1.0f, 3.0f, 5.0f, 1.0f,
				3.0f, 5.0f, 7.0f, 9.0f);
	
	//** Çà·Ä BÀÇ Á¤ÀÇ
	XMMATRIX B( 2.0f, 6.0f, 6.0f, 4.0f,
				8.0f, 4.0f, 4.0f, 8.0f,
				6.0f, 2.0f, 6.0f, 6.0f,
				8.0f, 4.0f, 2.0f, 8.0f);



	//** Çà·ÄÀÇ °ö¼À
	XMMATRIX C = A * B;
	Output(C);


	//** Çà·ÄÀÇ µ¡¼À
	XMMATRIX D = A + B;
	Output(D);
	


	//** Çà·ÄÀÇ –E¼À
	XMMATRIX E = A - B;
	Output(E);


	//**  A + (B + C)  =  (A + B) + C
	XMMATRIX F = A + (B + C);
	XMMATRIX G = (A + B) + C;

	Output(F);
	Output(G);




	//** Çà·ÄÀÇ °ö¼À = XMMatrixMultiply( _t, _d)
	Output( XMMatrixMultiply(A, B));


	//** ´ÜÀ§Çà·Ä = XMMatrixIdentity()
	Output(XMMatrixIdentity());



	//** ÀüÄ¡ Çà·Ä = XMMatrixTranspose(_m)
	Output(XMMatrixTranspose(G));



	//** Çà·ÄÀÇ –E¼À
	XMMATRIX H = A * 2;
	Output(H);



	return 0;
}