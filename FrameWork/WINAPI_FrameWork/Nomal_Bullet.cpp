#include "Nomal_Bullet.h"
#include "Object.h"


Nomal_Bullet::Nomal_Bullet()
{

}

Nomal_Bullet::~Nomal_Bullet()
{

}


void Nomal_Bullet::Initialize(void)
{
	m_fSpeed = 3.f;
	m_fAngle = 0.f;
}

int Nomal_Bullet::Update(Transform& _Transform)
{
	_Transform.Position.fX += m_Direction.fX * m_fSpeed;
	_Transform.Position.fY += m_Direction.fY * m_fSpeed;

	if (_Transform.Position.fX - (_Transform.Scale.fX / 2) < 50 ||
		_Transform.Position.fY - (_Transform.Scale.fY / 2) < 50 ||
		_Transform.Position.fX + (_Transform.Scale.fX / 2) > (WINSIZEX - 50) ||
		_Transform.Position.fY + (_Transform.Scale.fY / 2) > (WINSIZEY - 50))
	{
		return S_FALSE;
	}

	return S_OK;
}

void Nomal_Bullet::Render(HDC _hdc)
{
	Ellipse(_hdc,
		int(m_pObject->GetPosition().fX - int(m_pObject->GetScale().fX / 2)),
		int(m_pObject->GetPosition().fY - int(m_pObject->GetScale().fY / 2)),
		int(m_pObject->GetPosition().fX + int(m_pObject->GetScale().fX / 2)),
		int(m_pObject->GetPosition().fY + int(m_pObject->GetScale().fY / 2)));
}

void Nomal_Bullet::Release(void)
{

}
