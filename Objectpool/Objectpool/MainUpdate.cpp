#include "MainUpdate.h"
#include "ObjectPool.h"
#include "Player.h"


MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{

}

void MainUpdate::Initialize()
{

}

void MainUpdate::Update()
{
	ObjectPool::GetInstance()->Update();

	if (GetAsyncKeyState(VK_UP))
	{
		Object* pObj = ObjectPool::GetInstance()->Findobject("Player");

		if (pObj == NULL)
		{
			ObjectPool::GetInstance()->Addobject();
		}
	}
}

void MainUpdate::Render()
{
	ObjectPool::GetInstance()->Render();
}

void MainUpdate::Release()
{

}
