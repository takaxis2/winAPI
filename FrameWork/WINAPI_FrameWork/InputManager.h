#pragma once
#include "Headers.h"


class InputManager
{
private:
	static InputManager* m_pInstance;
public:
	static InputManager* GetInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new InputManager;
		return m_pInstance;
	}
private:
	DWORD m_dwKey;
public:
	void InputUpdate();
public:
	DWORD GetKey() { return m_dwKey; }

	POINT GetMousePoint()
	{
		POINT pt;

		//** 마우스 좌표 받아오는 함수.
		GetCursorPos(&pt);

		//** 마우스 좌표를 현재 윈도우 창의 좌표로 변환.
		ScreenToClient(g_hWnd, &pt);

		return pt;
	}

private:
	InputManager();
public:
	~InputManager();
};

