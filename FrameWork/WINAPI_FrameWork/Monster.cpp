#include "framework.h"
#include "Monster.h"


Monster::Monster()
{

}

Monster::~Monster()
{

}


void Monster::Initialize(void)
{
	m_Transform.Position = Vector3(WINSIZEX / 2, -200);
	m_Transform.Rotation = Vector3(0, 0);
	m_Transform.Scale = Vector3(150, 150);

	m_Speed = 3.0f;

	m_bActive = true;
}

int Monster::Update(void)
{
	m_Transform.Position.fY += m_Speed;

	return S_OK;
}

void Monster::Render(HDC _hdc)
{
	Ellipse(_hdc,
		int(m_Transform.Position.fX - int(m_Transform.Scale.fX / 2)),
		int(m_Transform.Position.fY - int(m_Transform.Scale.fY / 2)),
		int(m_Transform.Position.fX + int(m_Transform.Scale.fX / 2)),
		int(m_Transform.Position.fY + int(m_Transform.Scale.fY / 2)));
}

void Monster::Release(void)
{

}
