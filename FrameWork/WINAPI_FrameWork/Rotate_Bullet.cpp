#include "Rotate_Bullet.h"
#include "Object.h"

Rotate_Bullet::Rotate_Bullet()
{

}

Rotate_Bullet::~Rotate_Bullet()
{

}


void Rotate_Bullet::Initialize(void)
{
	m_fSpeed = 15.f;
	m_fAngle = 0.f;
}

int Rotate_Bullet::Update(Transform& _Transform)
{
	_Transform.Position.fX += cosf(m_fAngle * PI / 180) * m_fSpeed;
	_Transform.Position.fY += -sinf(m_fAngle * PI / 180) * m_fSpeed;

	if (_Transform.Position.fX - (_Transform.Scale.fX / 2) < 50 ||
		_Transform.Position.fY - (_Transform.Scale.fY / 2) < 50 ||
		_Transform.Position.fX + (_Transform.Scale.fX / 2) > (WINSIZEX - 50) ||
		_Transform.Position.fY + (_Transform.Scale.fY / 2) > (WINSIZEY - 50))
	{
		return S_FALSE;
	}

	return S_OK;
}

void Rotate_Bullet::Render(HDC _hdc)
{
	Rectangle(_hdc,
		int(m_pObject->GetPosition().fX - int(m_pObject->GetScale().fX / 2)),
		int(m_pObject->GetPosition().fY - int(m_pObject->GetScale().fY / 2)),
		int(m_pObject->GetPosition().fX + int(m_pObject->GetScale().fX / 2)),
		int(m_pObject->GetPosition().fY + int(m_pObject->GetScale().fY / 2)));
}

void Rotate_Bullet::Release(void)
{

}
