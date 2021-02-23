#pragma once
#include "Headers.h"

class Object;
class Prototype;
class ObjectManager 
{
public:
	DECLARE_SINGLETON(ObjectManager);
private:
	list<Object*> m_EnableList;
	map<string, list<Object*>> m_DisableList;
public:
	Object** Addobject(string _strKey);
	void Update();
	void Render();
	void Release();
public:
	map<string, list<Object*>>* GetDisableList() { return &m_DisableList; }

private:
	ObjectManager();
public:
	~ObjectManager();
};

