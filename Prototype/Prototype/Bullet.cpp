#include "Bullet.h"
#include "CursorController.h"


Bullet::Bullet()
{

}

Bullet::Bullet(Transform _Transform) 
	: Object(_Transform)
{

}

Bullet::~Bullet()
{

}


void Bullet::Initialize()
{
	m_Transform.Position = Vector3(0, 0);
	m_Transform.Rotation = Vector3(0, 0);
	m_Transform.Scale = Vector3(4, 1);

	m_Active = false;
	m_strKey = "Bullet";
}

int Bullet::Update()
{
	m_Transform.Position.x += 3;

	if (m_Transform.Position.x >= 80)
		return 1;

	return 0;
}

void Bullet::Render()
{
	GET_SINGLE(CursorController)->SetCursorPosition(
		(int)m_Transform.Position.x, (int)m_Transform.Position.y, (char*)"¿Â«≥", 12);
}

void Bullet::Release()
{

}
