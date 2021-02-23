#pragma once
#include "Headers.h"

class Scene
{
public:
	virtual void Initialize(void)PURE;
	virtual void Update(void)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;
public:
	Scene();
	virtual ~Scene();
};
