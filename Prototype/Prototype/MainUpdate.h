#pragma once
#include "Headers.h"

class Object;
class MainUpdate
{
private:
	list<Object*> m_pBulletList;
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
public:
	MainUpdate();
	~MainUpdate();
};



/*************************************************************
 * Objetpool 현재 생성만 진행함.
 * EnableList 로 돌아온 객체를 찾아 다시 사용할 수 있게 만들어보자.
**************************************************************/