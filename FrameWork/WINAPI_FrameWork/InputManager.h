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

		//** ���콺 ��ǥ �޾ƿ��� �Լ�.
		GetCursorPos(&pt);

		//** ���콺 ��ǥ�� ���� ������ â�� ��ǥ�� ��ȯ.
		ScreenToClient(g_hWnd, &pt);

		return pt;
	}

private:
	InputManager();
public:
	~InputManager();
};

