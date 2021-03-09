#include "MainUpdate.h"
#include "Device.h"
#include "Model.h"
#include "ColorShader.h"
#include "Camera.h"
#include "InputManager.h"


MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{
	Release();
}


void MainUpdate::Initialize()
{
	m_hdc = GetDC(g_hWnd);

	if (FAILED(GET_SINGLE(Device)->Initialize((float)SCREENWIDTH, (float)SCREENHEIGHT)))
		MessageBox(g_hWnd, L"Could not initialize Direct3D.", L"Error", MB_OK);


	m_Camera = new Camera;
	m_Camera->Initialize();


	m_Model = new Model;

	//** �� ���� �� �ε��� ���۸� �׷��� ���������ο� ��ġ�Ͽ� �׸��⸦ �غ�.
	if (FAILED(m_Model->Initialize()))
		MessageBox(g_hWnd, L"Could not initialize the model object.", L"Error", MB_OK);


	m_ColorShader = new ColorShader;
	if (FAILED(m_ColorShader->Initialize()))
		MessageBox(g_hWnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
}

void MainUpdate::Update()
{
	GET_SINGLE(InputManager)->KeyCheck();


	//** ī�޶� ��ġ�� �������� �� ��Ʈ������ ����
	m_Camera->Update();
}

void MainUpdate::Render()
{
	//** �׸����� �����۸� ����
	GET_SINGLE(Device)->BeginPaint(0.0f, 0.0f, 0.0f, 1.0f);

	//** m_Camera ���� �� ����� ������
	XMMATRIX ViewMatrix;
	m_Camera->GetViewMatrix(ViewMatrix);

	//** Device ���� ����, ��������� ������
	XMMATRIX WorldMatrix;
	GET_SINGLE(Device)->GetWorldMatrix(WorldMatrix);

	XMMATRIX ProjectionMatrix;
	GET_SINGLE(Device)->GetProjectionMatrix(ProjectionMatrix);

	//** ���� ���̴��� ����Ͽ� ���� �������մϴ�.
	if (FAILED(m_ColorShader->Render(m_Model->GetIndexCount(),
		WorldMatrix, ViewMatrix, ProjectionMatrix))) {
		return;
	}

	//** �������� ����� ȭ�鿡 ǥ���մϴ�.
	GET_SINGLE(Device)->EndPaint();
}

void MainUpdate::Release()
{
	Safe_Delete(m_Model);
	Safe_Delete(m_Camera);
	Safe_Delete(m_ColorShader);

	DESTROY_SINGLE(Device);
}


