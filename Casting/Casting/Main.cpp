#include <iostream>

using namespace std;


typedef unsigned char BYTE;



//** 클레스 전방 선언.
class Pen;
class Desk;
class Chair;



//** 클레스 정의
class Person					 //  <-- 
{								 //    |
public:							 //    |
	void Output()				 //    |
	{							 //    |
		cout << "Person" << endl;//    |
	}							 //    |
};								 //    |
								 //    |
class Student : public Person	 //  <-- [is - a 관계]	//	  <-- 
{														//		|
private:				//**  has - a 관계				//		|
	Pen*	m_pPen;		//** 학생이 펜을 갖을수 있음.	//		|
	Desk*	m_pDesk;	//** 학생이 책상을 갖을수 있음. //		|
	Chair*	m_pChair;	//** 학생이 의자를 갖을수 있음. //		|
public:													//		|
	void Output()										//		|
	{													//		|
		cout << "Student" << endl;						//		|
	}													//		|
};														//		|
														//		|
														//		|
class Boy : public Student	// <<---------[ is - a 관계	]--------
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
	//** 참고 자료 https://docs.microsoft.com/ko-kr/cpp/cpp/static-cast-operator?view=msvc-160
	
	
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
	//** dynamic_cast;  //** 암시적 캐스팅.
	//** 참고 자료 https://docs.microsoft.com/ko-kr/cpp/cpp/dynamic-cast-operator?view=msvc-160



	/*
	//** 다운 캐스팅.
	Person* pPerson1 = new Person;
	Person* pPerson2 = new Student;

	Person* Test1 = dynamic_cast<Person*>(pPerson1);
	Person* Test2 = dynamic_cast<Person*>(pPerson2);

	Test1->Output();
	Test2->Output();
	*/




	/*
	//** 업 캐스팅.
	Boy* pc = dynamic_cast<Boy*>(_Boy);
	Student* pb = dynamic_cast<Student*>(_Boy);

	pc->Output();
	pb->Output();
	*/




	/*
	Pen* m_pPen;
	Person* Test3 = dynamic_cast<Person*>(m_pPen);
	*/

	//** 오류내용 : 런타임 dynamic_cast의 피연산자는 다형 클래스 형식이어야 합니다.
	//** 상속관계가 아니기 때문에 사용이 불가함.
}


void Reinterpret_cast()
{
	//** reinterpret_cast
	//** 참고 자료 https://docs.microsoft.com/ko-kr/cpp/cpp/reinterpret-cast-operator?view=msvc-160
	//** 데이터의 크기는 같은데 자료형이 다를 때 강제제 값을 할당함.


	A* a = new A;
	a->SetNumber(10);

	B* b = reinterpret_cast<B*>(a);


	a->Output();
	b->Output();
}





//** Pen 클레스 함수 정의
void Pen::SetNumber(int _iNumber)
{
	m_iNumber = _iNumber;
}

void Pen::Const_cast() const
{
	//** const_cast
	//** 참고 자료 https://docs.microsoft.com/ko-kr/cpp/cpp/const-cast-operator?view=msvc-160

	cout << endl << "Before: " << m_iNumber;
	const_cast<Pen*>(this)->m_iNumber--;
	cout << endl << "After: " << m_iNumber;
}
