#pragma once
#include "Object.h"

class Monster : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	virtual Object* Clone() { return new Monster(*this); }
public:
	Monster();
	Monster(Transform _Transform);
	virtual ~Monster();
};