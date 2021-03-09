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
	//** 위쪽을 가리키는 벡터를 설정.
	XMFLOAT3 Up = m_Up;

	//** 카메라 위치를 설정.
	XMFLOAT3 Position = m_Position;

	//** 카메라가 바라보고 있는 방향.
	XMFLOAT3 LookAt = m_LookAt;

	//** UP 방향 벡터를 XMVECTOR 형으로 변경.
	XMVECTOR vecUp = XMLoadFloat3(&Up);

	//** Position 벡터를 XMVECTOR 형으로 변경.
	XMVECTOR vecPosition = XMLoadFloat3(&Position);

	//** 바라보는(?) 보고싶은(?) 방향 벡터를 XMVECTOR 형으로 변경.
	XMVECTOR vecLookAt = XMLoadFloat3(&LookAt);

	//** 바라볼(?) 방향 벡터를 MVECTOR 형으로 셋팅.
	XMVECTOR vecForward = XMVector3Normalize(vecLookAt - vecPosition);


	//** XMVECTOR => XMFLOAT3 형 변환.
	XMStoreFloat3(&m_Forward, vecForward);
	/*********************************
		m_Forward = XMFLOAR3
		vecForward = XMVECTOR
	**********************************/


	//** 외적을 통해 우측 혹은 좌측 방향을 바라보는(?) 바라볼(?) 벡터를 구함.
	XMVECTOR vecRight = XMVector3Normalize(XMVector3Cross(vecUp, vecForward));


	//** XMVECTOR => XMFLOAT3 형 변환.
	XMStoreFloat3(&m_Right, vecRight);
	/*********************************
		m_Right = XMFLOAR3
		vecRight = XMVECTOR
	**********************************/

	/*
	//** 회전된 카메라 위치를 뷰어 위치로 변환.
	LookAt.x += Position.x;
	LookAt.y += Position.y;
	LookAt.z += Position.z;
	*/


	/**************************************************
	 * 여기까지 진행 되었다면 필요한 재료는 모두 만들었음.
	 * 이제 재료를 사용해서 방향만 정해주면 됨.
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


	//** 드레그 중인지 확인 하기 위함.
	bool m_bViewCheck = false;


	//** 최초 드레그 했을때.. 
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



	//** 벡터로 변환.
	XMVECTOR EyePosition = XMLoadFloat3(&m_Position);
	XMVECTOR FocusPosition = XMLoadFloat3(&m_LookAt);


	//** 마지막으로 업데이트된 세 벡터에서 뷰 매트릭스를 만듭니다.
	/************************************************************************************************
	 * EyePosition : 카메라 위치 => Camera
	 * FocusPosition : 타겟 위치.   카메라 초점 위치.  카메라가 바라보고 있는 위치. => Target
	 * vecUp :  카메라가 타겟을 바라볼 때의 위쪽 방향.  - Game world 의 위쪽 방향 =>  y축 방향
	*************************************************************************************************/
	m_CameraViewMatrix = XMMatrixLookAtLH(EyePosition, FocusPosition, vecUp);
}