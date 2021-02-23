#pragma once
#include "Bridge.h"

class Bridge_Bullet : public Bridge 
{
protected:
	float m_fSpeed;
	float m_fAngle;
	Vector3 m_Direction;
public:
	virtual void Initialize(void)PURE;
	virtual int Update(Transform& _Transform)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;
public:
	void SetDirection(Vector3 _Direction) { m_Direction.fX = _Direction.fX; m_Direction.fY = _Direction.fY; }
	void SetAngle(float  _fAngle) { m_fAngle = _fAngle; }
public:
	Bridge_Bullet() {};
	virtual ~Bridge_Bullet() {};
};

