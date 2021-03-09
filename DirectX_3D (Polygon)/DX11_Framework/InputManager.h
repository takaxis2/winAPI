#pragma once
#include "Headers.h"

class InputManager
{
public:
	DECLARE_SINGLETON(InputManager)
private:
	ULONG m_luKey;
public:
	ULONG GetKey() { return m_luKey; }

	void KeyCheck()
	{
		m_luKey = 0;

		if (GetAsyncKeyState(VK_UP) & 0x8000|| 
			GetAsyncKeyState('W') & 0x8000)
			m_luKey |= INPUTID::UP;

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 ||
			GetAsyncKeyState('S') & 0x8000)
			m_luKey |= INPUTID::DOWN;

		if (GetAsyncKeyState(VK_LEFT) & 0x8000 ||
			GetAsyncKeyState('A') & 0x8000)
			m_luKey |= INPUTID::LEFT;

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 ||
			GetAsyncKeyState('D') & 0x8000)
			m_luKey |= INPUTID::RIGHT;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			m_luKey |= INPUTID::SPACE;

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			m_luKey |= INPUTID::ESCAPE;

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			m_luKey |= INPUTID::RETURN;

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			m_luKey |= INPUTID::MOUSE_LBOTTON;

		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			m_luKey |= INPUTID::MOUSE_RBOTTON;
	}

	POINT GetMousePosition()
	{
		//** 마우스 좌표를 정장하기 위한 변수.
		POINT ptMouse;

		//** 마우스 좌표를 받아옴.
		GetCursorPos(&ptMouse);

		//** 받아온 좌표를 현재 윈도우 창의 좌표로 변환.
		ScreenToClient(g_hWnd, &ptMouse);

		//** 반환.
		return ptMouse;
	}


private:
	InputManager();
	~InputManager();
};

