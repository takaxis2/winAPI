#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	virtual Object* Clone() { return new Bullet(*this); }
public:
	Bullet();
	Bullet(Transform _Transform);
	virtual ~Bullet();
};