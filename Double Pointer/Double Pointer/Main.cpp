#include <iostream>
#include <vector>
#include <list>
#include <map>


using namespace std;




typedef struct tagVector3
{
	float fX = 0;
	float fY = 0;
	float fZ = 0;

	tagVector3() {};

	tagVector3(float _fX, float _fY, float _fZ)
		: fX(_fX), fY(_fY), fZ(_fZ) {};

	tagVector3(float _fX, float _fY) : fX(_fX), fY(_fY), fZ(0) {};

}Vector3;





void Coll_by_Value(int, int);
void Coll_by_Reference(int*, int*);
void Coll_by_Reference(int& _i, int& _n);


/**********************
*      1. Pointer      
***********************/

int main(void)
{
	//** ������ 1

	/*
	
	int i = 100;
	int* pN = &i;

	cout << "pN �� �ּ�: " << (&pN) << endl;
	cout << "pN �� ��:   " << (*pN) << endl;
	cout << "i ��  ��:   " << i << endl;
	cout << "i �� �ּ� : " << (&i) << endl;
	
	cout << "pN ����Ű�� �ּ�: " << pN << endl;

	*/







	//** ������ 2
	/*
	//** ������ ũ�� ����. (�ʱ�ȭ �ƴ�.)
	Temp->fX = 1;
	Vector3* Temp = (Vector3*)malloc(sizeof(Vector3));

	//Vector3* Temp = new Vector3;

	//** �ʱ�ȭ.
	Temp->fY = 10;
	Temp->fZ = 100;
	*/








	//** ������ 3

	/*
	int iArray[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int* pIter = iArray;


	//** ��� 1

	for (int i = 0; i < 8; i++)
	{
		cout << pIter[i] << endl;
	}
	*/


	/*
	//** ��� 2
	for (int i = 0; i < 8; i++)
	{
		cout << (*pIter+i) << endl;
	}
	*/

	//** ��� 3
	/*
	for (int i = 0; i < 8; i++)
	{
		cout << (*pIter++) << endl;
	}
	*/






	

	//** ������ 4  (Double Pointer)
	/*
	int iNumber = 100;		//** iNumber  
	int* piNum = &iNumber;	//** iNumber  <-  piNum
	int** ppiNum = &piNum;	//** iNumber  <-  piNum  <--  ppiNum


	cout << "iNumber �� ��   : " << iNumber << endl;
	cout << "iNumber �� �ּ� : " << &iNumber << endl << endl;


	cout << "piNum �� ��   : " << (*piNum) << endl;
	cout << "piNum �� ����Ű�� �ּ� : " << piNum << endl;
	cout << "piNum �� �ּ� : " << &piNum << endl << endl;


	cout << "ppiNum �� ��   : " << (**ppiNum) << endl;
	cout << "ppiNum �� ����Ű�� �ּ� : " << ppiNum << endl;
	cout << "ppiNum �� �ּ� : " << &ppiNum << endl;
	*/









	//** ������ 1 (Reference)

	/*
	int i = 100;
	int& rN = i;


	cout << rN << endl;
	cout << &rN << endl;
	cout << &i << endl;

	*/



	//** ������ 2 (Reference)

	/***********************************
		Reference = read only

		int& rN = 10;  //** error

		int&& rriNumber = 10; // ����
	***********************************/


	/*
	int i = 10, n = 20;

	Coll_by_Value(i, n);

	cout << i << endl << n << endl;
	*/

	


	/*
	Coll_by_Reference(&i, &n);

	cout << i << ", " << &i << endl;
	cout << n << ", " << &n << endl << endl;
	*/




	/*
	Coll_by_Reference(i, n);

	cout << i << ", " << &i << endl;
	cout << n << ", " << &n << endl;
	*/

	return 0;
}



//** Coll-by-Value : ���� ����
void Coll_by_Value(int _i, int _n)
{
	_i = 100;
	_n = 200;
}

//** Coll-by-Reference : �ּҸ� ����
void Coll_by_Reference(int* _i, int* _n)
{
	*_i = 100;
	*_n = 200;

	cout << (*_i) << ", " << &_i << endl;
	cout << (*_n) << ", " << &_n << endl << endl;
}

//** Coll-by-Reference : �ּҸ� ����
void Coll_by_Reference(int& _i, int& _n)
{
	_i = 1000;
	_n = 2000;

	cout << _i << ", " << &_i << endl;
	cout << _n << ", " << &_n << endl << endl;
}



