#pragma once
#include "Object.h"

class Monster : public Object
{
private:
	float m_Speed;
public:
	virtual void Initialize(void)override;
	virtual int Update(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Monster();
	virtual ~Monster();
};

