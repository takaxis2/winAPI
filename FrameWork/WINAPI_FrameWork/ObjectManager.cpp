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
	//** 매개변수로 들어온 객체가 기존 map 컨테이너에 있는지 확인.
	map<string, list<Object*>>::iterator iter = m_mapObjectList.find(_pObject->GetKey());

	//** 만약에 없다면
	if (iter == m_mapObjectList.end())
	{
		//** map 에 넣을 리스트를 생성
		list<Object*> TempList;

		//** 리스트에 객체를 추가.
		TempList.push_back(_pObject);

		//** 그리고 객체가 추가된 리스트를 map에 추가.
		m_mapObjectList.insert(make_pair(_pObject->GetKey(), TempList));
	}
	else //** 있다면
		iter->second.push_back(_pObject);	//** 검색이 완료된 iter 를 사용해 객체를 추가.
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
	begin()		= 첫번째 원소를 가르키는 반복자
	end()		= 마지막 (원소 아님) 을 가르키는 반복자
	capacity()	= vector의 크기 (할당된 공간의 크기)
	size()		= vector의 원소 갯수
	at( i )		= Index 로 접근 가능 [직접 접근가능]
	front()		= 첫번째 원소를 참조
	back()		= 마지막 원소를 참조
	clear()		= vector의 정보를 전체 삭제
	insert( p , x )	= p가 가리키는 위치에 x 를 삽입
	erase( p )		= p가 가리키는 원소를 삭제
	max_size()		= vector의 최대 저장 가능한 원소의 갯수
	rbegin()		= vector의 역순의 첫번째 원소를 가리키는 반복자
	rend()			= vector의 역순의 마지막을 가리키는 반복자
	pop_back()		= 마지막 원소를 삭제
	push_back(x)		= 마지막에 x 를 추가한다.
	reserve( n )		= n 만큼의 크기를 재할당 한다.
	resize( n )		= n 만큼의 사이즈를 재할당 하고 추가되는 공간에는 '0' 으로 초기화 됨.
	resize( n, x )	= n 만큼의 사이즈를 재할당 하고 추가되는 공간에는 'x' 로 초기화 됨.
	swap()			= 2개의 vector 을  swap 함.
*/