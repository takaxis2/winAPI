#pragma once
#include "Headers.h"

class Object;
class Prototype;
class ObjectPool
{
public:
	DECLARE_SINGLETON(ObjectPool);
private:
	Prototype* m_pPrototype;
public:
	Object* Findobject(string _strKey);
public:
	void Intialize();
	void Update();
	void Render();
private:
	ObjectPool();
public:
	~ObjectPool();
};

