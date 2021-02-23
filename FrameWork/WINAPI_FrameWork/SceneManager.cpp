#include "framework.h"
#include "SceneManager.h"

#include "Logo.h"
#include "Menu.h"
#include "Stage.h"


SceneManager* SceneManager::m_pInstance = NULL;


SceneManager::SceneManager()
	: m_pSceneState(NULL)
{

}

SceneManager::~SceneManager()
{

}

//** �� �Լ��� ȣ��Ǿ��ٴ°��� ���� �ѱ������.
void SceneManager::SetScene(SCENEIDS _SceneID)
{
	//** ���࿡ m_pSceneState �����ΰ� ����ִٸ�...
	if (m_pSceneState != NULL)
	{
		//** ����
		delete m_pSceneState;
		m_pSceneState = NULL;
	}

	//** �� ���� ��....
	switch (_SceneID)
	{
	case SCENEID_LOGO:
		m_pSceneState = new Logo;
		break;
	case SCENEID_MENU:
		m_pSceneState = new Menu;
		break;
	case SCENEID_STAGE:
		m_pSceneState = new Stage;
		break;
	case SCENEID_EXIT:

		break;
	}
	//** �ʱ�ȭ.
	m_pSceneState->Initialize();
}

void SceneManager::Update(void)
{
	m_pSceneState->Update();
}

void SceneManager::Render(HDC _hdc)
{
	m_pSceneState->Render(_hdc);
}
