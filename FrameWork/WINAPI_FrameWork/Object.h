#pragma once
#include "Headers.h"


class Object
{
protected:
	Transform m_Transform;
	string m_strKey;
	bool m_bActive;

public:
	virtual void Initialize(void)PURE;
	virtual int Update(void)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;
public:
	//** 객체의 현재 상태가 사용되고 있는 상태인지, 
	//** 혹은 비 사용 상태인지 확인하기 위함
	bool GetActive() { return m_bActive; }

	//** 현재 상태를 변경함
	void SetActive(bool _bActive) { m_bActive = _bActive; }

	string GetKey() const { return m_strKey; }
	void SetKey(string _strKey) { m_strKey = _strKey; }

	Vector3 GetPosition() const { return m_Transform.Position; }
	void SetPosition(Vector3 _Position) {  m_Transform.Position.fX = _Position.fX; m_Transform.Position.fY = _Position.fY; }
	
	Vector3 GetScale() const { return m_Transform.Scale; }
	void SetScale(Vector3 _Scale) { m_Transform.Scale.fX = _Scale.fX; m_Transform.Scale.fY = _Scale.fY; }
public:
	Object();
	virtual ~Object();
};

