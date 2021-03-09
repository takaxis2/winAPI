#pragma once
#include "Headers.h"
#include "AlignedAllocationPolicy.h"

class Camera : public AlignedAllocationPolicy<16>
{
private:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_LookAt;

	XMFLOAT3 m_Up;
	XMFLOAT3 m_Right;
	XMFLOAT3 m_Forward;


	XMMATRIX m_CameraViewMatrix;

	//** �̵� �ӵ�
	float m_fSpeed;

	//** ȸ�� ����.
	float m_fAngle;


	//** �巹�� ������ ���콺 ��ǥ
	POINT m_ptMouse;

public:
	void Initialize();
	void Update();
public:
	void SetPosition(XMFLOAT3 _Position) { m_Position = _Position; }
	void SetRotation(XMFLOAT3 _Rotation) { m_Rotation = _Rotation; }
	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	void GetViewMatrix(XMMATRIX& _CameraViewMatrix) { _CameraViewMatrix = m_CameraViewMatrix; }
public:
	Camera();
	~Camera();
};

