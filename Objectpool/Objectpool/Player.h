#pragma once
#include "Object.h"

class Player : public Object
{
private:
	int m_Count;
public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	Player();
	virtual ~Player();
};

