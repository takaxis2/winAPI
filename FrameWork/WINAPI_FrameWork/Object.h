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
	//** ��ü�� ���� ���°� ���ǰ� �ִ� ��������, 
	//** Ȥ�� �� ��� �������� Ȯ���ϱ� ����
	bool GetActive() { return m_bActive; }

	//** ���� ���¸� ������
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

