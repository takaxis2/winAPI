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
 * Objetpool ���� ������ ������.
 * EnableList �� ���ƿ� ��ü�� ã�� �ٽ� ����� �� �ְ� ������.
**************************************************************/