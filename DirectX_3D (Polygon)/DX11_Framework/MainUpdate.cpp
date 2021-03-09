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

	//** 모델 정점 및 인덱스 버퍼를 그래픽 파이프라인에 배치하여 그리기를 준비.
	if (FAILED(m_Model->Initialize()))
		MessageBox(g_hWnd, L"Could not initialize the model object.", L"Error", MB_OK);


	m_ColorShader = new ColorShader;
	if (FAILED(m_ColorShader->Initialize()))
		MessageBox(g_hWnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
}

void MainUpdate::Update()
{
	GET_SINGLE(InputManager)->KeyCheck();


	//** 카메라 위치를 기준으로 뷰 매트릭스를 생성
	m_Camera->Update();
}

void MainUpdate::Render()
{
	//** 그리기전 모든버퍼를 지움
	GET_SINGLE(Device)->BeginPaint(0.0f, 0.0f, 0.0f, 1.0f);

	//** m_Camera 에서 뷰 행렬을 가져옴
	XMMATRIX ViewMatrix;
	m_Camera->GetViewMatrix(ViewMatrix);

	//** Device 에서 월드, 투영행렬을 가져옴
	XMMATRIX WorldMatrix;
	GET_SINGLE(Device)->GetWorldMatrix(WorldMatrix);

	XMMATRIX ProjectionMatrix;
	GET_SINGLE(Device)->GetProjectionMatrix(ProjectionMatrix);

	//** 색상 셰이더를 사용하여 모델을 렌더링합니다.
	if (FAILED(m_ColorShader->Render(m_Model->GetIndexCount(),
		WorldMatrix, ViewMatrix, ProjectionMatrix))) {
		return;
	}

	//** 렌더링된 장면을 화면에 표시합니다.
	GET_SINGLE(Device)->EndPaint();
}

void MainUpdate::Release()
{
	Safe_Delete(m_Model);
	Safe_Delete(m_Camera);
	Safe_Delete(m_ColorShader);

	DESTROY_SINGLE(Device);
}


