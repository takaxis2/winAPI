#include "Player.h"
#include "CursorController.h"
#include "ObjectManager.h"
#include "Bullet.h"

Player::Player()
{

}

Player::Player(Transform _Transform)
	: Object(_Transform)
{

}

Player::~Player()
{

}


void Player::Initialize()
{
	m_Transform.Position = Vector3(10, 5);
	m_Transform.Rotation = Vector3(0, 0);
	m_Transform.Scale = Vector3(2, 1);

	m_Active = false;
}

int Player::Update()
{
	if (GetAsyncKeyState(VK_UP))
	{
		m_Transform.Position.y -= 1;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_Transform.Position.y += 1;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_Transform.Position.x -= 2;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_Transform.Position.x += 2;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		Object** ppBullet = GET_SINGLE(ObjectManager)->Addobject("Bullet");
		(*ppBullet)->SetPosition(m_Transform.Position);
	}
	
	return 0;
}

void Player::Render()
{
	GET_SINGLE(CursorController)->SetCursorPosition(
		(int)m_Transform.Position.x, (int)m_Transform.Position.y, (char*)"¿Ê", 15);
}

void Player::Release()
{

}
