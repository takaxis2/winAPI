#include "ColorShader.h"
#include "Device.h"

ColorShader::ColorShader()
	: m_vertexShader(0),
	m_pixelShader(0),
	m_layout(0),
	m_matrixBuffer(0)
{

}

ColorShader::~ColorShader()
{

}

UINT ColorShader::Initialize()
{
	bool result; 
	
	// ���� ���̴��� �ȼ� ���̴��� �ʱ�ȭ�մϴ�. 
	result = InitializeShader(L"../Shader/SampleVS.hlsl", L"../Shader/SamplePS.hlsl"); 
	
	if(!result) { return S_FALSE; } 
	
	return S_OK; 
}

void ColorShader::Release()
{
	//** ���� ���̴��� �Ƚ� ���̴� �� �׿� ���õ� �͵��� ��ȯ�մϴ�.
	if (m_matrixBuffer) { SAFE_RELEASE(m_matrixBuffer); }	//** ��� ���۸� �����մϴ�.
	if (m_layout) { SAFE_RELEASE(m_layout); }			//** ���̾ƿ��� �����մϴ�. 
	if (m_pixelShader) { SAFE_RELEASE(m_pixelShader); }	//** �ȼ� ���̴��� �����մϴ�. 
	if (m_vertexShader) { SAFE_RELEASE(m_vertexShader); }	//** ���� ���̴��� �����մϴ�. 
}

UINT ColorShader::Render(int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	bool result; 
	
	//** �������� ����� ���̴��� ���ڸ� �Է��մϴ�. 
	result = SetShaderParameters(
		worldMatrix,
		viewMatrix,
		projectionMatrix);
	
	if(!result) 
	{ 
		return S_FALSE; 
	} 
	

	//** ���̴��� �̿��Ͽ� �غ�� ���۸� �׸��ϴ�. 
	//** ���� �Է� ���̾ƿ��� �����մϴ�. 
	GET_SINGLE(Device)->GetDeviceContext()->IASetInputLayout(m_layout);

	//** �ﰢ���� �׸� ���� ���̴��� �ȼ� ���̴��� �����մϴ�. 
	GET_SINGLE(Device)->GetDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	GET_SINGLE(Device)->GetDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	//** �ﰢ���� �׸��ϴ�. 
	GET_SINGLE(Device)->GetDeviceContext()->DrawIndexed(indexCount, 0, 0);
	GET_SINGLE(Device)->GetDeviceContext()->Draw(indexCount, 0);
	
	return S_OK;
}

UINT ColorShader::InitializeShader(LPCWSTR vsFilename, LPCWSTR psFilename)
{
	ID3D10Blob* errorMessage = NULL;
	ID3D10Blob* vertexShaderBuffer = NULL; 
	ID3D10Blob* pixelShaderBuffer = NULL;


	HRESULT result;
	//** ���� ���̴� 
	result = D3DCompileFromFile(
		vsFilename, //** ��� �� ���� �̸�.
		NULL,	 //** ���̴� ��ũ��
		NULL,	 //** ���̴� �ڵ忡 ��ũ��带 �� �� ���⶧���� �߰� �Ҽ� �ִ� ��ũ�� �ۼ�.
		"main", //** ���̴� ���� �̸�
		"vs_5_0",	 //** ���̴� ���� DirectX 11 ������ vs_5_0 �� ���.
		0,		//** HLSL �ڵ带 �������ϴ� ����� ����. 0 = ������� ����.
		0,		//** �����Ϸ��� ����. ������� ����.
		&vertexShaderBuffer,//** ���̴��� �޾ƿ�.
		&errorMessage);	//** ���� ������ �޾ƿ�.

	if (FAILED(result))
	{
		//** ���̴��� �����Ͽ� �����ϸ� ���� �޼����� ���
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, vsFilename);
		}
		//** ���� �޼����� ���ٸ� ���̴� ������ ã�� ���� ��
		else
		{
			MessageBox(g_hWnd, (LPCWSTR)vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	//** �ȼ� ���̴��� ������
	result = D3DCompileFromFile((LPCWSTR)psFilename, NULL, NULL, "main", "ps_5_0", 
		0, NULL, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		//** ���̴� �������� �����ϸ� ���� �޼����� ���
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, psFilename);
		}
		//** ���� �޼����� ���ٸ� �ܼ��� ���̴� ������ ã�� ���� ��
		else
		{
			MessageBox(g_hWnd, (LPCWSTR)psFilename, L"Missing Shader File", MB_OK);
		}

		return S_FALSE;
	}

	//** ���۷κ��� ���� ���̴��� �����մϴ�.
	result = GET_SINGLE(Device)->GetDevice()->CreateVertexShader(
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), 
		NULL, &m_vertexShader);
	if(FAILED(result)) { return false; } 


	//** ���۷κ��� �ȼ� ���̴��� �����մϴ�. 
	result = GET_SINGLE(Device)->GetDevice()->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), 
		NULL, &m_pixelShader);
	if(FAILED(result)) { return false; }


	//** ���� �Է� ���̾ƿ� description�� �ۼ�
	//** �� ������ Model Class�� ���̴��� �ִ� VertexType�� ��ġ�ؾ� �մϴ�. 
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	//** ���̾ƿ��� ��� ������ ������
	UINT numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]); 
	

	//** ���� �Է� ���̾ƿ��� ����
	result = GET_SINGLE(Device)->GetDevice()->CreateInputLayout(
		polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	
	if(FAILED(result)) { return false; } 
	

	//** �� �̻� ������ �ʴ� ���� ���̴� ���ۿ� �ȼ� ���̴� ���۸� ����
	SAFE_RELEASE(vertexShaderBuffer);
	SAFE_RELEASE(pixelShaderBuffer);

	//** ���� ���̴��� �ִ� ��� ��� ������ description�� �ۼ�
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC; 
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType); 
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; 
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
	matrixBufferDesc.MiscFlags = 0; 
	matrixBufferDesc.StructureByteStride = 0; 
	

	//** ��� ���� �����͸� ����� �� Ŭ�������� ���� ���̴� ��� ���ۿ� ������ �� �ְ� ��
	result = GET_SINGLE(Device)->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if(FAILED(result)) 
	{ 
		return S_FALSE;
	}

	return S_OK;
}

void ColorShader::OutputShaderErrorMessage(ID3D10Blob* _errorMessage, LPCWSTR _Filename)
{
	//** ���� �޼����� ��� �ִ� ���ڿ� ������ �����͸� ������
	char* CompileErrors = (char*)(_errorMessage->GetBufferPointer());

	//** �޼����� ���̸� ������
	ULONG BufferSize = _errorMessage->GetBufferSize();

	//** ������ ���� �ȿ� �޼����� ���
	ofstream Fout;
	Fout.open("shader-error.txt");

	//** ���� �޼���
	for (ULONG i = 0; i < BufferSize; i++) { Fout << CompileErrors[i]; }

	//** ������ ����
	Fout.close();

	//** ���� �޼����� ��ȯ
	SAFE_RELEASE(_errorMessage);

	//** ������ ������ ������ �˾� �޼����� �˷���
	MessageBox(g_hWnd, L"Error compiling shader. Check shader-error.txt for message.", _Filename, MB_OK);

	return;
}


bool ColorShader::SetShaderParameters(XMMATRIX& _WorldMatrix, XMMATRIX& _ViewMatrix, XMMATRIX& _ProjectionMatrix)
{
	//** ����� transpose�Ͽ� ���̴����� ����� �� �ְ� ��.
	_ViewMatrix = XMMatrixTranspose(_ViewMatrix);
	_WorldMatrix = XMMatrixTranspose(_WorldMatrix);
	_ProjectionMatrix = XMMatrixTranspose(_ProjectionMatrix);
	
	HRESULT result; 

	//** ��� ������ ������ �� �� �ֵ��� ���.
	D3D11_MAPPED_SUBRESOURCE mappedResource; 
	result = GET_SINGLE(Device)->GetDeviceContext()->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result)) { return false; } 
	

	//** ��� ������ �����Ϳ� ���� �����͸� ������.
	MatrixBufferType* DataPtr = (MatrixBufferType*)mappedResource.pData;
	
	//** ��� ���ۿ� ����� ����.
	DataPtr->View = _ViewMatrix;
	DataPtr->World = _WorldMatrix;
	DataPtr->Projection = _ProjectionMatrix;
	
	//** ��� ������ ����� ǰ.
	GET_SINGLE(Device)->GetDeviceContext()->Unmap(m_matrixBuffer, 0);
	
	//** ���� ���̴������� ��� ������ ��ġ�� ����.
	UINT BufferNumber = 0;
	
	//** ���������� ���� ���̴��� ��� ���۸� �ٲ� ������ �ٲ�.
	GET_SINGLE(Device)->GetDeviceContext()->VSSetConstantBuffers(BufferNumber, 1, &m_matrixBuffer);
	
	return true; 
}