#include "Camera.h"
#include "InputManager.h"
#include "MathManager.h"

Camera::Camera() :
	m_Position(XMFLOAT3(0.0f, 0.0f, 0.0f)),
	m_Rotation(XMFLOAT3(0.0f, 0.0f, 0.0f)),
	m_LookAt(XMFLOAT3(0.0f, 0.0f, 0.0f)),
	m_Up(XMFLOAT3(0.0f, 0.0f, 0.0f)),
	m_fAngle(0), m_fSpeed(0)
{

}

Camera::~Camera()
{

}

void Camera::Initialize()
{
	m_Position = XMFLOAT3(0.0f, 2.0f, -10.0f);
	m_LookAt = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_Up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	m_fSpeed = 0.2f;
	m_fAngle = 0;
}

void Camera::Update()
{
	//** ������ ����Ű�� ���͸� ����.
	XMFLOAT3 Up = m_Up;

	//** ī�޶� ��ġ�� ����.
	XMFLOAT3 Position = m_Position;

	//** ī�޶� �ٶ󺸰� �ִ� ����.
	XMFLOAT3 LookAt = m_LookAt;

	//** UP ���� ���͸� XMVECTOR ������ ����.
	XMVECTOR vecUp = XMLoadFloat3(&Up);

	//** Position ���͸� XMVECTOR ������ ����.
	XMVECTOR vecPosition = XMLoadFloat3(&Position);

	//** �ٶ󺸴�(?) �������(?) ���� ���͸� XMVECTOR ������ ����.
	XMVECTOR vecLookAt = XMLoadFloat3(&LookAt);

	//** �ٶ�(?) ���� ���͸� MVECTOR ������ ����.
	XMVECTOR vecForward = XMVector3Normalize(vecLookAt - vecPosition);


	//** XMVECTOR => XMFLOAT3 �� ��ȯ.
	XMStoreFloat3(&m_Forward, vecForward);
	/*********************************
		m_Forward = XMFLOAR3
		vecForward = XMVECTOR
	**********************************/


	//** ������ ���� ���� Ȥ�� ���� ������ �ٶ󺸴�(?) �ٶ�(?) ���͸� ����.
	XMVECTOR vecRight = XMVector3Normalize(XMVector3Cross(vecUp, vecForward));


	//** XMVECTOR => XMFLOAT3 �� ��ȯ.
	XMStoreFloat3(&m_Right, vecRight);
	/*********************************
		m_Right = XMFLOAR3
		vecRight = XMVECTOR
	**********************************/

	/*
	//** ȸ���� ī�޶� ��ġ�� ��� ��ġ�� ��ȯ.
	LookAt.x += Position.x;
	LookAt.y += Position.y;
	LookAt.z += Position.z;
	*/


	/**************************************************
	 * ������� ���� �Ǿ��ٸ� �ʿ��� ���� ��� �������.
	 * ���� ��Ḧ ����ؼ� ���⸸ �����ָ� ��.
	***************************************************/


	ULONG luKey = GET_SINGLE(InputManager)->GetKey();


	if (luKey & INPUTID::UP)
	{
		m_Position.x += m_Forward.x * m_fSpeed;
		m_Position.y += m_Forward.y * m_fSpeed;
		m_Position.z += m_Forward.z * m_fSpeed;

		m_LookAt.x += m_Forward.x * m_fSpeed;
		m_LookAt.y += m_Forward.y * m_fSpeed;
		m_LookAt.z += m_Forward.z * m_fSpeed;
	}

	if (luKey & INPUTID::DOWN)
	{
		m_Position.x -= m_Forward.x * m_fSpeed;
		m_Position.y -= m_Forward.y * m_fSpeed;
		m_Position.z -= m_Forward.z * m_fSpeed;

		m_LookAt.x -= m_Forward.x * m_fSpeed;
		m_LookAt.y -= m_Forward.y * m_fSpeed;
		m_LookAt.z -= m_Forward.z * m_fSpeed;
	}

	if (luKey & INPUTID::LEFT)
	{
		m_Position.x += m_Right.x * m_fSpeed;
		m_Position.y += m_Right.y * m_fSpeed;
		m_Position.z += m_Right.z * m_fSpeed;

		m_LookAt.x += m_Right.x * m_fSpeed;
		m_LookAt.y += m_Right.y * m_fSpeed;
		m_LookAt.z += m_Right.z * m_fSpeed;
	}

	if (luKey & INPUTID::RIGHT)
	{
		m_Position.x -= m_Right.x * m_fSpeed;
		m_Position.y -= m_Right.y * m_fSpeed;
		m_Position.z -= m_Right.z * m_fSpeed;

		m_LookAt.x -= m_Right.x * m_fSpeed;
		m_LookAt.y -= m_Right.y * m_fSpeed;
		m_LookAt.z -= m_Right.z * m_fSpeed;
	}


	//** �巹�� ������ Ȯ�� �ϱ� ����.
	bool m_bViewCheck = false;


	//** ���� �巹�� ������.. 
	if (luKey & INPUTID::MOUSE_RBOTTON && !m_bViewCheck)
	{
		m_ptMouse = GET_SINGLE(InputManager)->GetMousePosition();
		m_bViewCheck = true;
	}

	Sleep(1);
	if (luKey & INPUTID::MOUSE_RBOTTON && m_bViewCheck)
	{
		POINT TempPoint = GET_SINGLE(InputManager)->GetMousePosition();

		float fDistance = GET_SINGLE(MathManager)->GetDistance(
			XMFLOAT3((float)m_ptMouse.x, (float)m_ptMouse.y, 0.0f),
			XMFLOAT3((float)TempPoint.x, (float)TempPoint.y, 0.0f));
		float fRatio = float((fDistance * 100) / SCREENWIDTH);


		if (m_ptMouse.x > TempPoint.x)
			m_LookAt.x += m_Right.x * 0.7f; 
		else
			m_LookAt.x -= m_Right.x * 0.7f;
		
		m_bViewCheck = false;
	}



	//** ���ͷ� ��ȯ.
	XMVECTOR EyePosition = XMLoadFloat3(&m_Position);
	XMVECTOR FocusPosition = XMLoadFloat3(&m_LookAt);


	//** ���������� ������Ʈ�� �� ���Ϳ��� �� ��Ʈ������ ����ϴ�.
	/************************************************************************************************
	 * EyePosition : ī�޶� ��ġ => Camera
	 * FocusPosition : Ÿ�� ��ġ.   ī�޶� ���� ��ġ.  ī�޶� �ٶ󺸰� �ִ� ��ġ. => Target
	 * vecUp :  ī�޶� Ÿ���� �ٶ� ���� ���� ����.  - Game world �� ���� ���� =>  y�� ����
	*************************************************************************************************/
	m_CameraViewMatrix = XMMatrixLookAtLH(EyePosition, FocusPosition, vecUp);
}