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
	 * �Լ� ȣ�� ������ ��������.
	 * 1. GET_SINGLE(ObjectPool)->Intialize();
	 * 2. GET_SINGLE(ObjectManager)->Addobject(_strKey);
	************************************************************/

	//** ��ü ������ ���� �����Ѵ�.
	GET_SINGLE(ObjectPool)->Intialize();




	//** ������ ���� ��ü�� ���� �ʿ��� ��ü�� ��������Ѵ�.
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
