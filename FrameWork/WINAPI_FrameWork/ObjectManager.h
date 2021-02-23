#pragma once
#include "Headers.h"

class Object;
class ObjectManager
{
private:
	//** 나 자신을 생성하기 위함.
	static ObjectManager* m_pInstance;
public:
	//** 나 자신에게 접근하기 위함.
	static ObjectManager* GetInstance()
	{
		//** 만약에 나 자신이 없다면..
		if (m_pInstance == NULL)
			//** 나를 동적할당 해줌.
			m_pInstance = new ObjectManager;

		//** 그리고 나 자신을 반환.
		return m_pInstance;
	}
//****************************************************
private:
	Object* m_pPlayer;
	map<string, list<Object*>> m_mapObjectList;
public:
	Object* GetPlayer() { return m_pPlayer; }
	void SetPlayer(Object* _pPlayer) { m_pPlayer = _pPlayer; } 

	list<Object*>* GetObjectList(string _strKey)
	{
		//** 탐색할 키값을 받아 리스트를 찾아옴.
		map<string, list<Object*>>::iterator iter = m_mapObjectList.find(_strKey);

		//** 동일한 키값으로 검색이 완료되면 리스트를 반환 하고
		if (iter != m_mapObjectList.end())
			return &iter->second;

		//* 아니면 NULL 을 반환.
		return NULL;
	}
//****************************************************
private:
	list<Object*> m_ActiveList;
public:
	Object* Findobject(string _strKey);
	

//****************************************************
public:
	void AddObject(Object* _pObject);
	void Update(void);
	void Render(HDC _hdc);
	void Release();
//****************************************************
private:
	ObjectManager();
public:
	~ObjectManager();
};

