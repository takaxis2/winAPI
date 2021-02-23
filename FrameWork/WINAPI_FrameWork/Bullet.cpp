#include "framework.h"
#include "Bullet.h"
#include "Bridge.h"

Bullet::Bullet() : m_pBridge(NULL)
{

}

Bullet::~Bullet()
{
	Release();
}

void Bullet::Initialize(void)
{
	m_Transform.Position = Vector3(0, 0);
	m_Transform.Rotation = Vector3(0, 0);
	m_Transform.Scale = Vector3(15, 15);
	m_bActive = true;
}

int Bullet::Update(void)
{
	int BulletState = 0;

	if (m_pBridge)
		BulletState = m_pBridge->Update(m_Transform);

	if (BulletState)
	{
		Safe_Delete(m_pBridge);
		return S_FALSE;
	}

	return S_OK;
}

void Bullet::Render(HDC _hdc)
{
	if (m_pBridge)
		m_pBridge->Render(_hdc);
}

void Bullet::Release(void)
{
	Safe_Delete(m_pBridge);
}
