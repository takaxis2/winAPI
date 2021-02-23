#include "MainUpdate.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CursorController.h"


MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{
	Release();
}


void MainUpdate::Initialize()
{
	GET_SINGLE(SceneManager)->SetScene(SCENEID_LOGO);
	GET_SINGLE(CursorController)->SetCursorHide();
}

void MainUpdate::Update()
{
	GET_SINGLE(SceneManager)->Update();
}

void MainUpdate::Render()
{
	GET_SINGLE(SceneManager)->Render();
}

void MainUpdate::Release()
{
	DESTROY_SINGLE(SceneManager);
	DESTROY_SINGLE(InputManager);
	DESTROY_SINGLE(CursorController);
}

