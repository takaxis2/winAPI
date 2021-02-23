#include <iostream>

using namespace std;


typedef unsigned char BYTE;



//** Ŭ���� ���� ����.
class Pen;
class Desk;
class Chair;



//** Ŭ���� ����
class Person					 //  <-- 
{								 //    |
public:							 //    |
	void Output()				 //    |
	{							 //    |
		cout << "Person" << endl;//    |
	}							 //    |
};								 //    |
								 //    |
class Student : public Person	 //  <-- [is - a ����]	//	  <-- 
{														//		|
private:				//**  has - a ����				//		|
	Pen*	m_pPen;		//** �л��� ���� ������ ����.	//		|
	Desk*	m_pDesk;	//** �л��� å���� ������ ����. //		|
	Chair*	m_pChair;	//** �л��� ���ڸ� ������ ����. //		|
public:													//		|
	void Output()										//		|
	{													//		|
		cout << "Student" << endl;						//		|
	}													//		|
};														//		|
														//		|
														//		|
class Boy : public Student	// <<---------[ is - a ����	]--------
{
public:
	void Output()
	{
		cout << "Boy" << endl;
	}
};



class Object
{

};

class Pen : public Object
{
private:
	int m_iNumber;
public:
	void SetNumber(int);
	void Const_cast() const;
};

class Desk : public Object
{

};

class Chair : public Object
{

};




class A
{
private:
	int i;
public:
	void SetNumber(int _i) { i = _i; }
	void Output()
	{
		cout << "A : " << i << endl;
	}
};

class B
{
private:
	int i;
public:
	void SetNumber(int _i) { i = _i; }
	void Output()
	{
		cout << "B : " << i << endl;
	}
};



void Static_cast();
void Dynamic_cast(Boy* _Boy);
void Reinterpret_cast();





int main(void)
{
	//** static_cast
	//Static_cast();


	//** dynamic_cast
	//Dynamic_cast(new Boy);


	//** const_cast
	/*
	Pen p;
	p.SetNumber(8);
	p.Const_cast();
	*/

	//** reinterpret_cast
	Reinterpret_cast();


	return 0;
}



void Static_cast()
{
	//** static_cast
	//** ���� �ڷ� https://docs.microsoft.com/ko-kr/cpp/cpp/static-cast-operator?view=msvc-160
	
	
	char c;
	int i = 65;
	float f = 2.5;
	double db;


	c = static_cast<char>(i);
	db = static_cast<double>(f);
	i = static_cast<BYTE>(c);


	cout << c << endl;
	cout << db << endl;
	cout << i << endl;
}

void Dynamic_cast(Boy* _Boy)
{
	//** dynamic_cast;  //** �Ͻ��� ĳ����.
	//** ���� �ڷ� https://docs.microsoft.com/ko-kr/cpp/cpp/dynamic-cast-operator?view=msvc-160



	/*
	//** �ٿ� ĳ����.
	Person* pPerson1 = new Person;
	Person* pPerson2 = new Student;

	Person* Test1 = dynamic_cast<Person*>(pPerson1);
	Person* Test2 = dynamic_cast<Person*>(pPerson2);

	Test1->Output();
	Test2->Output();
	*/




	/*
	//** �� ĳ����.
	Boy* pc = dynamic_cast<Boy*>(_Boy);
	Student* pb = dynamic_cast<Student*>(_Boy);

	pc->Output();
	pb->Output();
	*/




	/*
	Pen* m_pPen;
	Person* Test3 = dynamic_cast<Person*>(m_pPen);
	*/

	//** �������� : ��Ÿ�� dynamic_cast�� �ǿ����ڴ� ���� Ŭ���� �����̾�� �մϴ�.
	//** ��Ӱ��谡 �ƴϱ� ������ ����� �Ұ���.
}


void Reinterpret_cast()
{
	//** reinterpret_cast
	//** ���� �ڷ� https://docs.microsoft.com/ko-kr/cpp/cpp/reinterpret-cast-operator?view=msvc-160
	//** �������� ũ��� ������ �ڷ����� �ٸ� �� ������ ���� �Ҵ���.


	A* a = new A;
	a->SetNumber(10);

	B* b = reinterpret_cast<B*>(a);


	a->Output();
	b->Output();
}





//** Pen Ŭ���� �Լ� ����
void Pen::SetNumber(int _iNumber)
{
	m_iNumber = _iNumber;
}

void Pen::Const_cast() const
{
	//** const_cast
	//** ���� �ڷ� https://docs.microsoft.com/ko-kr/cpp/cpp/const-cast-operator?view=msvc-160

	cout << endl << "Before: " << m_iNumber;
	const_cast<Pen*>(this)->m_iNumber--;
	cout << endl << "After: " << m_iNumber;
}
