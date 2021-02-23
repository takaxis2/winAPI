#include "framework.h"
#include "MainUpdate.h"

#include "SceneManager.h"
#include "InputManager.h"


MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{
	Release();
}


void MainUpdate::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);

	SceneManager::GetInstance()->SetScene(SCENEID_STAGE);
}

void MainUpdate::Update(void)
{
	InputManager::GetInstance()->InputUpdate();

	SceneManager::GetInstance()->Update();
}

void MainUpdate::Render(void)
{
	Rectangle(m_hdc, 0, 0, WINSIZEX, WINSIZEY);

	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Release(void)
{
	ReleaseDC(g_hWnd, m_hdc);
}
