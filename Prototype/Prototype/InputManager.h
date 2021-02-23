#pragma once
#include "Headers.h"

class InputManager
{
public:
	DECLARE_SINGLETON(InputManager);
private:
	InputManager();
public:
	~InputManager();
};