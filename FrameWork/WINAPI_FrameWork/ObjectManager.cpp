#include "framework.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

#include "Player.h"
#include "Bullet.h"

ObjectManager* ObjectManager::m_pInstance = NULL;


ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	Release();
}


Object* ObjectManager::Findobject(string _strKey)
{
	list<Object*>* ObjList = GetObjectList(_strKey);

	if (ObjList == NULL)
		return NULL;


	if (ObjList->empty())
		return NULL;


	Object* pObj = ObjList->back();
	m_ActiveList.push_back(pObj);
	ObjList->pop_back();

	return pObj;
}

void ObjectManager::AddObject(Object* _pObject)
{
	//** �Ű������� ���� ��ü�� ���� map �����̳ʿ� �ִ��� Ȯ��.
	map<string, list<Object*>>::iterator iter = m_mapObjectList.find(_pObject->GetKey());

	//** ���࿡ ���ٸ�
	if (iter == m_mapObjectList.end())
	{
		//** map �� ���� ����Ʈ�� ����
		list<Object*> TempList;

		//** ����Ʈ�� ��ü�� �߰�.
		TempList.push_back(_pObject);

		//** �׸��� ��ü�� �߰��� ����Ʈ�� map�� �߰�.
		m_mapObjectList.insert(make_pair(_pObject->GetKey(), TempList));
	}
	else //** �ִٸ�
		iter->second.push_back(_pObject);	//** �˻��� �Ϸ�� iter �� ����� ��ü�� �߰�.
}

void ObjectManager::Update(void)
{
	m_pPlayer->Update();

	for (map<string, list<Object*>>::iterator iter = m_mapObjectList.begin();
		iter != m_mapObjectList.end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
		{
			if((*iter2)->GetActive())
				(*iter2)->Update();
		}
	}

	list<Object*>* MonsterList = GetObjectList("Monster"); 
	list<Object*>* NomalBulletList = GetObjectList("NomalBullet");

	if (MonsterList != NULL && NomalBulletList != NULL)
		for (list<Object*>::iterator iter = MonsterList->begin();
			iter != MonsterList->end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = NomalBulletList->begin();
			iter2 != NomalBulletList->end(); ++iter2)
		{
			if (CollisionManager::Collision((*iter), (*iter2)))
			{
				(*iter)->SetActive(false);
				(*iter2)->SetActive(false);
			}
		}
	}
}

void ObjectManager::Render(HDC _hdc)
{
	m_pPlayer->Render(_hdc);

	for (map<string, list<Object*>>::iterator iter = m_mapObjectList.begin();
		iter != m_mapObjectList.end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
		{
			if ((*iter2)->GetActive())
				(*iter2)->Render(_hdc);
		}
	}
}

void ObjectManager::Release()
{
	SAFE_DELETE(m_pPlayer);

	for (map<string, list<Object*>>::iterator iter = m_mapObjectList.begin();
		iter != m_mapObjectList.end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
		{
			SAFE_DELETE(*iter2);
		}
		iter->second.clear();
	}
	m_mapObjectList.clear();
}



/*
	begin()		= ù��° ���Ҹ� ����Ű�� �ݺ���
	end()		= ������ (���� �ƴ�) �� ����Ű�� �ݺ���
	capacity()	= vector�� ũ�� (�Ҵ�� ������ ũ��)
	size()		= vector�� ���� ����
	at( i )		= Index �� ���� ���� [���� ���ٰ���]
	front()		= ù��° ���Ҹ� ����
	back()		= ������ ���Ҹ� ����
	clear()		= vector�� ������ ��ü ����
	insert( p , x )	= p�� ����Ű�� ��ġ�� x �� ����
	erase( p )		= p�� ����Ű�� ���Ҹ� ����
	max_size()		= vector�� �ִ� ���� ������ ������ ����
	rbegin()		= vector�� ������ ù��° ���Ҹ� ����Ű�� �ݺ���
	rend()			= vector�� ������ �������� ����Ű�� �ݺ���
	pop_back()		= ������ ���Ҹ� ����
	push_back(x)		= �������� x �� �߰��Ѵ�.
	reserve( n )		= n ��ŭ�� ũ�⸦ ���Ҵ� �Ѵ�.
	resize( n )		= n ��ŭ�� ����� ���Ҵ� �ϰ� �߰��Ǵ� �������� '0' ���� �ʱ�ȭ ��.
	resize( n, x )	= n ��ŭ�� ����� ���Ҵ� �ϰ� �߰��Ǵ� �������� 'x' �� �ʱ�ȭ ��.
	swap()			= 2���� vector ��  swap ��.
*/