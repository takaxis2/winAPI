#include "InputManager.h"

InputManager* InputManager::m_pInstance = NULL;

InputManager::InputManager() : m_dwKey(0)
{
}

InputManager::~InputManager()
{
}


void InputManager::InputUpdate()
{
	m_dwKey = 0;

	if (GetAsyncKeyState('W') | GetAsyncKeyState(VK_UP))
	{
		m_dwKey |= KEY_UP;
	}

	if (GetAsyncKeyState('S') | GetAsyncKeyState(VK_DOWN))
	{
		m_dwKey |= KEY_DOWN;
	}

	if (GetAsyncKeyState('A') | GetAsyncKeyState(VK_LEFT))
	{
		m_dwKey |= KEY_LEFT;
	}

	if (GetAsyncKeyState('D') | GetAsyncKeyState(VK_RIGHT))
	{
		m_dwKey |= KEY_RIGHT;
	}

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_dwKey |= KEY_LBUTTON;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		m_dwKey |= KEY_RBUTTON;
	}
}
