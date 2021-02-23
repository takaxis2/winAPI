#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectPool.h"
#include "CreateProtoObject.h"
#include "Player.h"

Stage::Stage()
{

}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	/***********************************************************
	 * 함수 호출 순서를 주의하자.
	 * 1. GET_SINGLE(ObjectPool)->Intialize();
	 * 2. GET_SINGLE(ObjectManager)->Addobject(_strKey);
	************************************************************/

	//** 객체 원형을 먼저 생성한다.
	GET_SINGLE(ObjectPool)->Intialize();




	//** 생성된 원형 객체를 통해 필요한 객체를 복사생성한다.
	GET_SINGLE(ObjectManager)->Addobject("Player");
	GET_SINGLE(ObjectManager)->Addobject("Monster");
}

void Stage::Update()
{
	GET_SINGLE(ObjectManager)->Update();
}

void Stage::Render()
{
	GET_SINGLE(ObjectManager)->Render();
}

void Stage::Release()
{
	DESTROY_SINGLE(ObjectManager);
}
