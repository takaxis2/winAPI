#include "Model.h"
#include "Device.h"

Model::Model()
{
	m_VertexBuffer = 0;
	m_IndexBuffer = 0;
}

Model::~Model()
{

}

UINT Model::Initialize()
{
	//** 정점 버퍼와 인덱스 버퍼를 초기화합니다. 
	if (FAILED(InitBuffers()))
	{
		MessageBox(g_hWnd, L"Model::Initialize.", L"Error", MB_OK);
		return S_FALSE;
	}

	//** 정점 버퍼와 인덱스 버퍼를 그래픽스 파이프라인에 넣어 화면에 그릴 준비를 합니다.
	//** 정점 버퍼의 단위와 오프셋을 설정합니다. 
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	//** input assembler에 정점 버퍼를 활성화하여 그려질 수 있게 합니다. 
	GET_SINGLE(Device)->GetDeviceContext()->IASetVertexBuffers(
		0, 1, &m_VertexBuffer, &stride, &offset);

	//** input assembler에 인덱스 버퍼를 활성화하여 그려질 수 있게 합니다. 
	GET_SINGLE(Device)->GetDeviceContext()->IASetIndexBuffer(
		m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//** 정점 버퍼로 그릴 기본형을 삼각형으로 설정합니다.
	GET_SINGLE(Device)->GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return S_OK;
}

void Model::Update()
{

}

//** 정점 버퍼와 인덱스 버퍼를 해제합니다. 
void Model::Release()
{
	if (m_IndexBuffer) { SAFE_RELEASE(m_IndexBuffer); }	//** 인덱스 버퍼를 해제합니다.
	if (m_VertexBuffer) { SAFE_RELEASE(m_VertexBuffer); }	//** 정점 버퍼를 해제합니다. 
}

UINT Model::InitBuffers()
{
	HRESULT result;


	//** 인덱스 배열을 생성
	VertexType Vertices[] =
	{
		{XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-1.0f, -1.0f,  1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-1.0f,  1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-1.0f,  1.0f,  1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(1.0f, -1.0f,  1.0f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(1.0f,  1.0f, -1.0f),  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(1.0f,  1.0f,  1.0f),  XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)},
		/*
			   6		   7
			   x___________x
			  /|		  /│
			 / |	   3 / │
		  2 *─┼────*   │
			│ x-------┼---x 8
			│ / 5	   │ /
			│/		   │/
		   1 *──────* 4
		*/
	};

	//** 정점 배열의 길이를 설정
	m_VertexCount = ARRAYSIZE(Vertices);

	//** 인덱스 출력 순서 설정.
	ULONG Indices[] = {
		 0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
	};

	//** 인덱스 배열의 길이를 설정
	m_IndexCount = ARRAYSIZE(Indices);

	//** 정점 버퍼의 구성요소를 셋팅.
	D3D11_BUFFER_DESC VertexBufferDesc;
	::ZeroMemory(&VertexBufferDesc, sizeof(VertexBufferDesc));

	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.ByteWidth = sizeof(VertexType) * m_VertexCount;
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.MiscFlags = 0;
	VertexBufferDesc.StructureByteStride = 0;



	//** 정점 데이터를 가리키는 리소스 구조체를 작성.
	D3D11_SUBRESOURCE_DATA VertexData;
	::ZeroMemory(&VertexData, sizeof(VertexData));

	VertexData.pSysMem = Vertices;
	VertexData.SysMemPitch = 0;
	VertexData.SysMemSlicePitch = 0;


	//** 정점 버퍼를 생성.
	result = GET_SINGLE(Device)->GetDevice()->CreateBuffer(
		&VertexBufferDesc, &VertexData, &m_VertexBuffer);
	if (FAILED(result)) { return S_FALSE; }


	//** 인덱스 버퍼의 구성요소를 셋팅.
	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = sizeof(unsigned long) * m_IndexCount;
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;
	IndexBufferDesc.StructureByteStride = 0;


	//** 인덱스 데이터를 가리키는 리소스 구조체를 작성.
	D3D11_SUBRESOURCE_DATA IndexData;
	IndexData.pSysMem = Indices;
	IndexData.SysMemPitch = 0;
	IndexData.SysMemSlicePitch = 0;


	//** 인덱스 버퍼 생성
	result = GET_SINGLE(Device)->GetDevice()->CreateBuffer(
		&IndexBufferDesc, &IndexData, &m_IndexBuffer);
	if (FAILED(result)) { return S_FALSE; }


	//** 정점 버퍼와 인덱스 버퍼를 해제
	//SafeDeleteArray(Vertices);
	//SafeDeleteArray(Indices);

	return S_OK;
}