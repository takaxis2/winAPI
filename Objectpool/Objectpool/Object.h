#pragma once
#include "Headers.h"

class Object
{
protected:
	string m_strKey;
	bool m_Active;

public:
	virtual void Initialize()PURE;
	virtual int Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
public:
	bool GetActive() { return m_Active; }
	void SetActive(bool _Active) { m_Active = _Active; }
public:
	Object();
	virtual ~Object();
};

