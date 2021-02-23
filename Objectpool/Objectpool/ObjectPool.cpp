#include "ObjectPool.h"
#include "Player.h"

ObjectPool* ObjectPool::m_pInstance = NULL;

ObjectPool::ObjectPool()
{
}

ObjectPool::~ObjectPool()
{
}


void ObjectPool::Addobject()
{
	for (int i = 0; i < 5; ++i)
	{
		Object* pObj = new Player;
		pObj->Initialize();
		m_ObjectList.push_back(pObj);
	}

	m_ActiveList.push_back(m_ObjectList.back());
	m_ObjectList.pop_back();
}

Object * ObjectPool::Findobject(string _strKey)
{
	if (m_ObjectList.empty())
		return NULL;

	Object* pObj = m_ObjectList.back();
	pObj->Initialize();
	pObj->SetActive(true);

	m_ActiveList.push_back(pObj);
	m_ObjectList.pop_back();

	return pObj;
}

void ObjectPool::Update()
{
	int iResult = 0;

	for (list<Object*>::iterator iter = m_ActiveList.begin();
		iter != m_ActiveList.end(); ++iter)
	{
		iResult = (*iter)->Update();

		if (iResult)
		{
			(*iter)->SetActive(false);
		}
	}

	for (list<Object*>::iterator iter = m_ActiveList.begin();
		iter != m_ActiveList.end(); )
	{
		if (!(*iter)->GetActive())
		{
			m_ObjectList.push_back((*iter));
			iter = m_ActiveList.erase(iter);
		}
		else
			++iter;
	}
}

void ObjectPool::Render()
{
	cout << "ActiveList : " << m_ActiveList.size() << endl;

	for (list<Object*>::iterator iter = m_ActiveList.begin();
		iter != m_ActiveList.end(); ++iter)
	{	
		(*iter)->Render();
	}
	cout << endl << endl;

	cout << "ObjectList : " << m_ObjectList.size() << endl;
	for (list<Object*>::iterator iter = m_ObjectList.begin();
		iter != m_ObjectList.end(); ++iter)
	{
		(*iter)->Render();
	}
}
