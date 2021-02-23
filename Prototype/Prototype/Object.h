#pragma once
#include "Headers.h"

class Object
{
protected:
	Transform m_Transform;
	bool m_Active;
	string m_strKey;
public:
	virtual void Initialize()PURE;
	virtual int Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
public:
	string GetKey() { return m_strKey; }

	virtual Object* Clone()PURE;

	Vector3 GetPosition() { return m_Transform.Position; }
	void SetPosition(Vector3 _Position) { m_Transform.Position = _Position; }

	bool GetActive() { return m_Active; }
	void SetActive(bool _Active) { m_Active = _Active; }
public:
	Object();
	Object(Transform _Transform);
	virtual ~Object();
};

