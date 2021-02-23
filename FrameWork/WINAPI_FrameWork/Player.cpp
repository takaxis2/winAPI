#include "framework.h"
#include "Player.h"
#include "Bullet.h"
#include "Nomal_Bullet.h"
#include "Rotate_Bullet.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "InputManager.h"
#include "CollisionManager.h"


Player::Player()
{

}

Player::~Player()
{

}


void Player::Initialize(void)
{
	m_Transform.Position = Vector3(WINSIZEX / 2, WINSIZEY - 100);
	m_Transform.Rotation = Vector3(0, 0);
	m_Transform.Scale = Vector3(100, 100);

	m_fSpeed = 5.f;
	m_fAngle = 0.f;

	m_bActive = true;
	m_strKey = "Player";

	m_BulletTime = GetTickCount64();
}

int Player::Update(void)
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();


	if (dwKey & KEY_UP)
	{
		m_Transform.Position.fY -= m_fSpeed;
		m_fAngle += 5;
	}
	if (dwKey & KEY_DOWN)
	{
		m_Transform.Position.fY += m_fSpeed;
		m_fAngle -= 5;
	}
	if (dwKey & KEY_LEFT)
	{
		m_Transform.Position.fX -= m_fSpeed;
	}
	if (dwKey & KEY_RIGHT)
	{
		m_Transform.Position.fX += m_fSpeed;
	}

	if (m_BulletTime + 150 < GetTickCount64())
	{
		if (dwKey & KEY_LBUTTON)
		{
			CreateNomalBullet<Nomal_Bullet>("NomalBullet");
			m_BulletTime = GetTickCount64();
		}
	}

	if (dwKey & KEY_RBUTTON)
	{
		CreateRotateBullet<Rotate_Bullet>();
	}
	

	return S_OK;
}

void Player::Render(HDC _hdc)
{
	Ellipse(_hdc, 
		int(m_Transform.Position.fX - int(m_Transform.Scale.fX / 2)),
		int(m_Transform.Position.fY - int(m_Transform.Scale.fY / 2)),
		int(m_Transform.Position.fX + int(m_Transform.Scale.fX / 2)), 
		int(m_Transform.Position.fY + int(m_Transform.Scale.fY / 2)));
}

void Player::Release(void)
{

}

template<typename T>
inline void Player::CreateNomalBullet(string _strKey)
{
	Bridge* pBridge = new T;

	Object* pObj = ObjectManager::GetInstance()->Findobject(_strKey);



	//** ���콺 ��ǥ �޾ƿ�
	POINT pt = InputManager::GetInstance()->GetMousePoint();

	//** �ﰢ�Լ��� ���� ����.
	float fWidth = pt.x - m_Transform.Position.fX;

	//** �ﰢ�Լ��� ���̸� ����.
	float fHeight = pt.y - m_Transform.Position.fY;

	//** ������ ���̸� ����.
	float fDistance = CollisionManager::GetDistance(Vector3((float)pt.x, (float)pt.y), m_Transform.Position);



	if (pObj == NULL)
	{
		pObj = ObjectFactory<Bullet>::CreateObject(m_Transform.Position, pBridge, _strKey);

		((Bridge_Bullet*)pBridge)->SetDirection(Vector3(fWidth / fDistance, fHeight / fDistance));
		ObjectManager::GetInstance()->AddObject(pObj);
	}
	else
	{
		pObj->Initialize();
		pObj->SetPosition(m_Transform.Position);

		((Nomal_Bullet*)((Bullet*)pObj)->GetBridge())->SetDirection(Vector3(fWidth / fDistance, fHeight / fDistance));

		pObj->SetActive(true);
	}
}

template<typename T>
inline void Player::CreateRotateBullet()
{
	Bridge* pBridge = new T;

	Object* pObj = ObjectFactory<Bullet>::CreateObject(m_Transform.Position, pBridge, "RotateBullet");

	//** ���콺 ��ǥ �޾ƿ�
	POINT pt = InputManager::GetInstance()->GetMousePoint();

	//** �ﰢ�Լ��� ���� ����.
	float fWidth = pt.x - m_Transform.Position.fX;

	//** �ﰢ�Լ��� ���̸� ����.
	float fHeight = pt.y - m_Transform.Position.fY;

	//** ������ ���̸� ����.
	float fDistance = CollisionManager::GetDistance(Vector3((float)pt.x, (float)pt.y), m_Transform.Position);

	//** ������ ����.
	m_fAngle = acosf(fWidth / fDistance) * 180 / PI;

	//** �÷��̾�� ���콺��ǥ�� �� �Ʒ��ʿ� �ִٸ�
	if (pt.y > m_Transform.Position.fY)
		//** ���� ���ص� ����� �ش�.
		m_fAngle *= -1;

	((Bridge_Bullet*)pBridge)->SetAngle(m_fAngle);

	ObjectManager::GetInstance()->AddObject(pObj);
}