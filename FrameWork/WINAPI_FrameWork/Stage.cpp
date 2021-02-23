#include "framework.h"
#include "Stage.h"

#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"


Stage::Stage()
{
}


Stage::~Stage()
{
	Release();
}


void Stage::Initialize(void)
{
	Object* pPlayer = ObjectFactory<Player>::CreateObject();
	ObjectManager::GetInstance()->SetPlayer(pPlayer);

	
	for (int i = 0; i < MonsterMax; ++i)
	{
		Object* pMonster = ObjectFactory<Monster>::CreateObject(
			Vector3(float(135 + i * 150), (float)-200), "Monster");

		ObjectManager::GetInstance()->AddObject(pMonster);
	}
}

void Stage::Update(void)
{
	ObjectManager::GetInstance()->Update();
}

void Stage::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Stage::Release(void)
{

}
