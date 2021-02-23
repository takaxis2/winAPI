#pragma once
#include "Object.h"

class Player : public Object
{
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	virtual Object* Clone() { return new Player(*this); }
public:
	Player();
	Player(Transform _Transform);
	virtual ~Player();
};
