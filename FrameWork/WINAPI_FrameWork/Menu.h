#pragma once
#include "Scene.h"

class Menu : public Scene
{
public:
	virtual void Initialize(void)override;
	virtual void Update(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Menu();
	virtual ~Menu();
};
