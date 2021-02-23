#pragma once
#include "Scene.h"

class Object;
class Stage : public Scene
{
public:
	virtual void Initialize(void)override;
	virtual void Update(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Stage();
	virtual ~Stage();
};

