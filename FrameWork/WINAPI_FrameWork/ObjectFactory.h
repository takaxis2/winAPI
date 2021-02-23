#pragma once
#include "Object.h"


template <typename T>
class ObjectFactory
{
public:
	static Object* CreateObject()
	{
		Object* pObj = new T;

		pObj->Initialize();

		return pObj;
	}

	static Object* CreateObject(Vector3 _Position)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_Position);

		return pObj;
	}

	static Object* CreateObject(Vector3 _Position, string _strKey)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_Position);

		pObj->SetKey(_strKey);
			
		return pObj;
	}

	static Object* CreateObject(Vector3 _Position, Bridge* _pBridge)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_Position);


		_pBridge->Initialize();

		_pBridge->SetObject(pObj);

		((Bullet*)pObj)->SetBridge(_pBridge);

		return pObj;
	}

	static Object* CreateObject(Vector3 _Position, Bridge* _pBridge, string _strKey)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_Position);
		pObj->SetKey(_strKey);

		_pBridge->Initialize();
		_pBridge->SetObject(pObj);

		((Bullet*)pObj)->SetBridge(_pBridge);

		return pObj;
	}
}; 