#pragma once
#include "Headers.h"

class MainUpdate
{
private:
	HDC m_hdc;
public:
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);
public:
	MainUpdate();
	~MainUpdate();
};


/***********************************************
 * �Ѿ� ����.
 * �Ѿ��� Angle ������ ���콺 ������ �������� �߻�.
************************************************/