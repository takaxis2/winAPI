#pragma once
#include "Headers.h"

class CursorController
{
public:
	DECLARE_SINGLETON(CursorController);
public:
	void SetCursorPosition(int _ix, int _iy, char* str, int _Color = 15);
	void SetCursorPosition(int _ix, int _iy, int _value, int _Color = 15);
	void SetCursorHide();
	void SetColor(int _Color);
private:
	CursorController();
private:
	~CursorController();
};

