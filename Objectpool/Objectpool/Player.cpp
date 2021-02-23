#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}


void Player::Initialize()
{
	m_strKey = "Player";
	m_Active = true;
	m_Count = 100;
}

int Player::Update()
{
	if ((--m_Count) <= 0)
	{
		return 1;
	}
	return 0;
}

void Player::Render()
{
	cout << "Player : " << m_Count << endl;
}

void Player::Release()
{

}
