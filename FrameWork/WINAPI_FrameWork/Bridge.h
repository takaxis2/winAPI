#pragma once
#include "Headers.h"

class Object;
class Bridge
{
protected:
	Object* m_pObject;
public:
	virtual void Initialize(void)PURE;
	virtual int Update(Transform& _Transform)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;
public:
	void SetObject(Object* _pObject) { m_pObject = _pObject; }
public:
	Bridge() { }
	virtual ~Bridge() { }
};