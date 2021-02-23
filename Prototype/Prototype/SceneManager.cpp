#include "SceneManager.h"
#include "Logo.h"
#include "Menu.h"
#include "Stage.h"


SceneManager::SceneManager() : SceneState(NULL)
{

}

SceneManager::~SceneManager()
{
	Release();
}


void SceneManager::SetScene(SCENEIDS _SceneID)
{
	if (SceneState != NULL)
		SAFE_RELEARE(SceneState);

	switch (_SceneID)
	{
	case SCENEID_LOGO:
		SceneState = new Logo;
		break;
	case SCENEID_MENU:
		SceneState = new Menu;
		break;
	case SCENEID_STAGE:
		SceneState = new Stage;
		break;
	case SCENEID_EXIT:
		exit(NULL);
		break;
	}
	SceneState->Initialize();
}

void SceneManager::Update()
{
	SceneState->Update();
}

void SceneManager::Render()
{
	SceneState->Render();
}

void SceneManager::Release()
{
	SAFE_RELEARE(SceneState);
}
