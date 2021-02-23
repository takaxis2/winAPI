#include "ObjectManager.h"
#include "CreateProtoObject.h"
#include "CursorController.h"
#include "ObjectPool.h"
#include "Object.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	Release();
}


Object** ObjectManager::Addobject(string _strKey)
{
	Object* pObj = GET_SINGLE(ObjectPool)->Findobject(_strKey);

	map<string, list<Object*>>::iterator iter = m_DisableList.find(_strKey);

	if (iter == m_DisableList.end())
		return NULL;

	m_EnableList.push_back(iter->second.back());
	iter->second.pop_back();

	return &pObj;
}

void ObjectManager::Update()
{
	int iResult = 0;

	/*
	for (map<string, list<Object*>>::iterator iter = m_DisableList.begin();
		iter != m_DisableList.end(); ++iter)
	{
	}
	*/

	map<string, list<Object*>>::iterator Bullet = m_DisableList.find("Bullet");

	if(!(Bullet == m_DisableList.end()))
		GET_SINGLE(CursorController)->SetCursorPosition(2, 2, Bullet->second.size());





	for (list<Object*>::iterator iter = m_EnableList.begin();
		iter != m_EnableList.end(); )
	{
		GET_SINGLE(CursorController)->SetCursorPosition(2, 1, m_EnableList.size());

		if ((*iter)->GetActive())
			iResult = (*iter)->Update();

		if (iResult == 1)
		{
			(*iter)->SetActive(false);

			map<string, list<Object*>>::iterator iter2 = m_DisableList.find((*iter)->GetKey());
			iter2->second.push_back((*iter));
			iter = m_EnableList.erase(iter);
		}
		else
			++iter;
	}
}

void ObjectManager::Render()
{
	for (list<Object*>::iterator iter2 = m_EnableList.begin();
		iter2 != m_EnableList.end(); ++iter2)
	{
		if ((*iter2)->GetActive())
			(*iter2)->Render();
	}
}

void ObjectManager::Release()
{
	for (map<string, list<Object*>>::iterator iter = m_DisableList.begin();
		iter != m_DisableList.end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
		{
			delete (*iter2);
			(*iter2) = NULL;
		}
		iter->second.clear();
	}
	m_DisableList.clear();
}


