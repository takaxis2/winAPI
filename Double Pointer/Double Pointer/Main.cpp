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
	//** 포인터 1

	/*
	
	int i = 100;
	int* pN = &i;

	cout << "pN 의 주소: " << (&pN) << endl;
	cout << "pN 의 값:   " << (*pN) << endl;
	cout << "i 의  값:   " << i << endl;
	cout << "i 의 주소 : " << (&i) << endl;
	
	cout << "pN 가르키는 주소: " << pN << endl;

	*/







	//** 포인터 2
	/*
	//** 포인터 크기 결정. (초기화 아님.)
	Temp->fX = 1;
	Vector3* Temp = (Vector3*)malloc(sizeof(Vector3));

	//Vector3* Temp = new Vector3;

	//** 초기화.
	Temp->fY = 10;
	Temp->fZ = 100;
	*/








	//** 포인터 3

	/*
	int iArray[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int* pIter = iArray;


	//** 출력 1

	for (int i = 0; i < 8; i++)
	{
		cout << pIter[i] << endl;
	}
	*/


	/*
	//** 출력 2
	for (int i = 0; i < 8; i++)
	{
		cout << (*pIter+i) << endl;
	}
	*/

	//** 출력 3
	/*
	for (int i = 0; i < 8; i++)
	{
		cout << (*pIter++) << endl;
	}
	*/






	

	//** 포인터 4  (Double Pointer)
	/*
	int iNumber = 100;		//** iNumber  
	int* piNum = &iNumber;	//** iNumber  <-  piNum
	int** ppiNum = &piNum;	//** iNumber  <-  piNum  <--  ppiNum


	cout << "iNumber 의 값   : " << iNumber << endl;
	cout << "iNumber 의 주소 : " << &iNumber << endl << endl;


	cout << "piNum 의 값   : " << (*piNum) << endl;
	cout << "piNum 이 가르키는 주소 : " << piNum << endl;
	cout << "piNum 의 주소 : " << &piNum << endl << endl;


	cout << "ppiNum 의 값   : " << (**ppiNum) << endl;
	cout << "ppiNum 이 가르키는 주소 : " << ppiNum << endl;
	cout << "ppiNum 의 주소 : " << &ppiNum << endl;
	*/









	//** 참조자 1 (Reference)

	/*
	int i = 100;
	int& rN = i;


	cout << rN << endl;
	cout << &rN << endl;
	cout << &i << endl;

	*/



	//** 참조자 2 (Reference)

	/***********************************
		Reference = read only

		int& rN = 10;  //** error

		int&& rriNumber = 10; // 가능
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



//** Coll-by-Value : 값을 복사
void Coll_by_Value(int _i, int _n)
{
	_i = 100;
	_n = 200;
}

//** Coll-by-Reference : 주소를 복사
void Coll_by_Reference(int* _i, int* _n)
{
	*_i = 100;
	*_n = 200;

	cout << (*_i) << ", " << &_i << endl;
	cout << (*_n) << ", " << &_n << endl << endl;
}

//** Coll-by-Reference : 주소를 복사
void Coll_by_Reference(int& _i, int& _n)
{
	_i = 1000;
	_n = 2000;

	cout << _i << ", " << &_i << endl;
	cout << _n << ", " << &_n << endl << endl;
}



