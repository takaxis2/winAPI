#pragma once
#include "Bridge_Bullet.h"

class Nomal_Bullet : public Bridge_Bullet
{
public:
	virtual void Initialize(void)override;
	virtual int Update(Transform& _Transform)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Nomal_Bullet();
	virtual ~Nomal_Bullet();
};

