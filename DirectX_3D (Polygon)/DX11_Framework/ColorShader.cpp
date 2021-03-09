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
	
	// 정점 셰이더와 픽셀 셰이더를 초기화합니다. 
	result = InitializeShader(L"../Shader/SampleVS.hlsl", L"../Shader/SamplePS.hlsl"); 
	
	if(!result) { return S_FALSE; } 
	
	return S_OK; 
}

void ColorShader::Release()
{
	//** 정점 셰이더와 픽실 셰이더 및 그와 관련된 것들을 반환합니다.
	if (m_matrixBuffer) { SAFE_RELEASE(m_matrixBuffer); }	//** 상수 버퍼를 해제합니다.
	if (m_layout) { SAFE_RELEASE(m_layout); }			//** 레이아웃을 해제합니다. 
	if (m_pixelShader) { SAFE_RELEASE(m_pixelShader); }	//** 픽셀 셰이더를 해제합니다. 
	if (m_vertexShader) { SAFE_RELEASE(m_vertexShader); }	//** 정점 셰이더를 해제합니다. 
}

UINT ColorShader::Render(int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	bool result; 
	
	//** 렌더링에 사용할 셰이더의 인자를 입력합니다. 
	result = SetShaderParameters(
		worldMatrix,
		viewMatrix,
		projectionMatrix);
	
	if(!result) 
	{ 
		return S_FALSE; 
	} 
	

	//** 셰이더를 이용하여 준비된 버퍼를 그립니다. 
	//** 정점 입력 레이아웃을 설정합니다. 
	GET_SINGLE(Device)->GetDeviceContext()->IASetInputLayout(m_layout);

	//** 삼각형을 그릴 정점 셰이더와 픽셀 셰이더를 설정합니다. 
	GET_SINGLE(Device)->GetDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	GET_SINGLE(Device)->GetDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	//** 삼각형을 그립니다. 
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
	//** 정점 셰이더 
	result = D3DCompileFromFile(
		vsFilename, //** 경로 및 파일 이름.
		NULL,	 //** 셰이더 매크로
		NULL,	 //** 셰이더 코드에 인크루드를 할 수 없기때문에 추가 할수 있는 매크로 작성.
		"main", //** 셰이더 매인 이름
		"vs_5_0",	 //** 셰이더 레벨 DirectX 11 버전은 vs_5_0 로 사용.
		0,		//** HLSL 코드를 컴파일하는 방법을 지정. 0 = 사용하지 않음.
		0,		//** 컴파일러가 결정. 사용하지 않음.
		&vertexShaderBuffer,//** 셰이더를 받아옴.
		&errorMessage);	//** 에러 내용을 받아옴.

	if (FAILED(result))
	{
		//** 셰이더가 컴파일에 실패하면 에러 메세지를 기록
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, vsFilename);
		}
		//** 에러 메세지가 없다면 셰이더 파일을 찾지 못한 것
		else
		{
			MessageBox(g_hWnd, (LPCWSTR)vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	//** 픽셀 셰이더를 컴파일
	result = D3DCompileFromFile((LPCWSTR)psFilename, NULL, NULL, "main", "ps_5_0", 
		0, NULL, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		//** 셰이더 컴파일이 실패하면 에러 메세지를 기록
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, psFilename);
		}
		//** 에러 메세지가 없다면 단순히 셰이더 파일을 찾지 못한 것
		else
		{
			MessageBox(g_hWnd, (LPCWSTR)psFilename, L"Missing Shader File", MB_OK);
		}

		return S_FALSE;
	}

	//** 버퍼로부터 정점 셰이더를 생성합니다.
	result = GET_SINGLE(Device)->GetDevice()->CreateVertexShader(
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), 
		NULL, &m_vertexShader);
	if(FAILED(result)) { return false; } 


	//** 버퍼로부터 픽셀 셰이더를 생성합니다. 
	result = GET_SINGLE(Device)->GetDevice()->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), 
		NULL, &m_pixelShader);
	if(FAILED(result)) { return false; }


	//** 정점 입력 레이아웃 description을 작성
	//** 이 설정은 Model Class와 셰이더에 있는 VertexType와 일치해야 합니다. 
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

	//** 레이아웃의 요소 갯수를 가져옴
	UINT numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]); 
	

	//** 정점 입력 레이아웃을 생성
	result = GET_SINGLE(Device)->GetDevice()->CreateInputLayout(
		polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	
	if(FAILED(result)) { return false; } 
	

	//** 더 이상 사용되지 않는 정점 셰이더 버퍼와 픽셀 셰이더 버퍼를 해제
	SAFE_RELEASE(vertexShaderBuffer);
	SAFE_RELEASE(pixelShaderBuffer);

	//** 정점 셰이더에 있는 행렬 상수 버퍼의 description을 작성
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC; 
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType); 
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; 
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
	matrixBufferDesc.MiscFlags = 0; 
	matrixBufferDesc.StructureByteStride = 0; 
	

	//** 상수 버퍼 포인터를 만들어 이 클래스에서 정점 셰이더 상수 버퍼에 접근할 수 있게 함
	result = GET_SINGLE(Device)->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if(FAILED(result)) 
	{ 
		return S_FALSE;
	}

	return S_OK;
}

void ColorShader::OutputShaderErrorMessage(ID3D10Blob* _errorMessage, LPCWSTR _Filename)
{
	//** 에러 메세지를 담고 있는 문자열 버퍼의 포인터를 가져옴
	char* CompileErrors = (char*)(_errorMessage->GetBufferPointer());

	//** 메세지의 길이를 가져옴
	ULONG BufferSize = _errorMessage->GetBufferSize();

	//** 파일을 열고 안에 메세지를 기록
	ofstream Fout;
	Fout.open("shader-error.txt");

	//** 에러 메세지
	for (ULONG i = 0; i < BufferSize; i++) { Fout << CompileErrors[i]; }

	//** 파일을 닫음
	Fout.close();

	//** 에러 메세지를 반환
	SAFE_RELEASE(_errorMessage);

	//** 컴파일 에러가 있음을 팝업 메세지로 알려쥼
	MessageBox(g_hWnd, L"Error compiling shader. Check shader-error.txt for message.", _Filename, MB_OK);

	return;
}


bool ColorShader::SetShaderParameters(XMMATRIX& _WorldMatrix, XMMATRIX& _ViewMatrix, XMMATRIX& _ProjectionMatrix)
{
	//** 행렬을 transpose하여 셰이더에서 사용할 수 있게 함.
	_ViewMatrix = XMMatrixTranspose(_ViewMatrix);
	_WorldMatrix = XMMatrixTranspose(_WorldMatrix);
	_ProjectionMatrix = XMMatrixTranspose(_ProjectionMatrix);
	
	HRESULT result; 

	//** 상수 버퍼의 내용을 쓸 수 있도록 잠금.
	D3D11_MAPPED_SUBRESOURCE mappedResource; 
	result = GET_SINGLE(Device)->GetDeviceContext()->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result)) { return false; } 
	

	//** 상수 버퍼의 데이터에 대한 포인터를 가져옴.
	MatrixBufferType* DataPtr = (MatrixBufferType*)mappedResource.pData;
	
	//** 상수 버퍼에 행렬을 복사.
	DataPtr->View = _ViewMatrix;
	DataPtr->World = _WorldMatrix;
	DataPtr->Projection = _ProjectionMatrix;
	
	//** 상수 버퍼의 잠금을 품.
	GET_SINGLE(Device)->GetDeviceContext()->Unmap(m_matrixBuffer, 0);
	
	//** 정점 셰이더에서의 상수 버퍼의 위치를 설정.
	UINT BufferNumber = 0;
	
	//** 마지막으로 정점 셰이더의 상수 버퍼를 바뀐 값으로 바꿈.
	GET_SINGLE(Device)->GetDeviceContext()->VSSetConstantBuffers(BufferNumber, 1, &m_matrixBuffer);
	
	return true; 
}