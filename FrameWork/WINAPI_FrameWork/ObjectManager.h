#pragma once
#include "Headers.h"

class Object;
class ObjectManager
{
private:
	//** �� �ڽ��� �����ϱ� ����.
	static ObjectManager* m_pInstance;
public:
	//** �� �ڽſ��� �����ϱ� ����.
	static ObjectManager* GetInstance()
	{
		//** ���࿡ �� �ڽ��� ���ٸ�..
		if (m_pInstance == NULL)
			//** ���� �����Ҵ� ����.
			m_pInstance = new ObjectManager;

		//** �׸��� �� �ڽ��� ��ȯ.
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
		//** Ž���� Ű���� �޾� ����Ʈ�� ã�ƿ�.
		map<string, list<Object*>>::iterator iter = m_mapObjectList.find(_strKey);

		//** ������ Ű������ �˻��� �Ϸ�Ǹ� ����Ʈ�� ��ȯ �ϰ�
		if (iter != m_mapObjectList.end())
			return &iter->second;

		//* �ƴϸ� NULL �� ��ȯ.
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

