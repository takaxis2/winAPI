#pragma once
#include "Headers.h"

class Object;
class ObjectPool
{
private:
	static ObjectPool* m_pInstance;
public:
	static ObjectPool* GetInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new ObjectPool;
		return m_pInstance;
	}
private:
	list<Object*> m_ObjectList;
	list<Object*> m_ActiveList;
public:
	void Addobject();
	Object* Findobject(string _strKey);
public:
	void Update();
	void Render();
private:
	ObjectPool();
public:
	~ObjectPool();
};

