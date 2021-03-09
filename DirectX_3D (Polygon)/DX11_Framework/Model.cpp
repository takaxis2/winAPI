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
	//** ���� ���ۿ� �ε��� ���۸� �ʱ�ȭ�մϴ�. 
	if (FAILED(InitBuffers()))
	{
		MessageBox(g_hWnd, L"Model::Initialize.", L"Error", MB_OK);
		return S_FALSE;
	}

	//** ���� ���ۿ� �ε��� ���۸� �׷��Ƚ� ���������ο� �־� ȭ�鿡 �׸� �غ� �մϴ�.
	//** ���� ������ ������ �������� �����մϴ�. 
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	//** input assembler�� ���� ���۸� Ȱ��ȭ�Ͽ� �׷��� �� �ְ� �մϴ�. 
	GET_SINGLE(Device)->GetDeviceContext()->IASetVertexBuffers(
		0, 1, &m_VertexBuffer, &stride, &offset);

	//** input assembler�� �ε��� ���۸� Ȱ��ȭ�Ͽ� �׷��� �� �ְ� �մϴ�. 
	GET_SINGLE(Device)->GetDeviceContext()->IASetIndexBuffer(
		m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//** ���� ���۷� �׸� �⺻���� �ﰢ������ �����մϴ�.
	GET_SINGLE(Device)->GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return S_OK;
}

void Model::Update()
{

}

//** ���� ���ۿ� �ε��� ���۸� �����մϴ�. 
void Model::Release()
{
	if (m_IndexBuffer) { SAFE_RELEASE(m_IndexBuffer); }	//** �ε��� ���۸� �����մϴ�.
	if (m_VertexBuffer) { SAFE_RELEASE(m_VertexBuffer); }	//** ���� ���۸� �����մϴ�. 
}

UINT Model::InitBuffers()
{
	HRESULT result;


	//** �ε��� �迭�� ����
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
			  /|		  /��
			 / |	   3 / ��
		  2 *������������*   ��
			�� x-------��---x 8
			�� / 5	   �� /
			��/		   ��/
		   1 *������������* 4
		*/
	};

	//** ���� �迭�� ���̸� ����
	m_VertexCount = ARRAYSIZE(Vertices);

	//** �ε��� ��� ���� ����.
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

	//** �ε��� �迭�� ���̸� ����
	m_IndexCount = ARRAYSIZE(Indices);

	//** ���� ������ ������Ҹ� ����.
	D3D11_BUFFER_DESC VertexBufferDesc;
	::ZeroMemory(&VertexBufferDesc, sizeof(VertexBufferDesc));

	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.ByteWidth = sizeof(VertexType) * m_VertexCount;
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.MiscFlags = 0;
	VertexBufferDesc.StructureByteStride = 0;



	//** ���� �����͸� ����Ű�� ���ҽ� ����ü�� �ۼ�.
	D3D11_SUBRESOURCE_DATA VertexData;
	::ZeroMemory(&VertexData, sizeof(VertexData));

	VertexData.pSysMem = Vertices;
	VertexData.SysMemPitch = 0;
	VertexData.SysMemSlicePitch = 0;


	//** ���� ���۸� ����.
	result = GET_SINGLE(Device)->GetDevice()->CreateBuffer(
		&VertexBufferDesc, &VertexData, &m_VertexBuffer);
	if (FAILED(result)) { return S_FALSE; }


	//** �ε��� ������ ������Ҹ� ����.
	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = sizeof(unsigned long) * m_IndexCount;
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;
	IndexBufferDesc.StructureByteStride = 0;


	//** �ε��� �����͸� ����Ű�� ���ҽ� ����ü�� �ۼ�.
	D3D11_SUBRESOURCE_DATA IndexData;
	IndexData.pSysMem = Indices;
	IndexData.SysMemPitch = 0;
	IndexData.SysMemSlicePitch = 0;


	//** �ε��� ���� ����
	result = GET_SINGLE(Device)->GetDevice()->CreateBuffer(
		&IndexBufferDesc, &IndexData, &m_IndexBuffer);
	if (FAILED(result)) { return S_FALSE; }


	//** ���� ���ۿ� �ε��� ���۸� ����
	//SafeDeleteArray(Vertices);
	//SafeDeleteArray(Indices);

	return S_OK;
}