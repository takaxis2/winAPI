#include "Monster.h"
#include "CursorController.h"


Monster::Monster()
{

}

Monster::Monster(Transform _Transform) 
	: Object(_Transform)
{

}

Monster::~Monster()
{

}


void Monster::Initialize()
{
	m_Transform.Position = Vector3(40, 5);
	m_Transform.Rotation = Vector3(0, 0);
	m_Transform.Scale = Vector3(2, 1);

	m_Active = false;
}

int Monster::Update()
{

	return 0;
}

void Monster::Render()
{
	GET_SINGLE(CursorController)->SetCursorPosition(
		(int)m_Transform.Position.x, (int)m_Transform.Position.y, (char*)"Ȫ", 15);
}

void Monster::Release()
{

}
