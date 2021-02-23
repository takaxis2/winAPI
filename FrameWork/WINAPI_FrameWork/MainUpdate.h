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
 * 총알 삭제.
 * 총알을 Angle 값으로 마우스 포인터 방향으로 발사.
************************************************/