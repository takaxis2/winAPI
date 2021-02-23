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

//** 이 함수가 호출되었다는것은 씬을 넘기기위함.
void SceneManager::SetScene(SCENEIDS _SceneID)
{
	//** 만약에 m_pSceneState 무엇인가 담겨있다면...
	if (m_pSceneState != NULL)
	{
		//** 삭제
		delete m_pSceneState;
		m_pSceneState = NULL;
	}

	//** 씬 선택 후....
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
	//** 초기화.
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
