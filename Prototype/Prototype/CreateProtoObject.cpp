#include "CreateProtoObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"


CreateProtoObject::CreateProtoObject()
{

}

CreateProtoObject::~CreateProtoObject()
{

}


//** ���� ��ü�� �����ϴ� �Լ�
int CreateProtoObject::InitProtoInstance()
{
	Transform TransInfo;

	m_mapObjectList.insert( make_pair( "Player", new Player(TransInfo)));
	m_mapObjectList.insert( make_pair( "Bullet", new Bullet(TransInfo)));
	m_mapObjectList.insert( make_pair( "Monster", new Monster(TransInfo)));

	return 0;
}