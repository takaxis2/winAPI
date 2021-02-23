#include "Device.h"

Device::Device()
{

}

Device::~Device()
{

}

void Device::Initialize(float _Width, float _Height, float _ScreenDepth, float _ScreenNear)
{
	InitalizeGPUInfo();
	CreateSwapChainAndDevice();
	CreateBackBuffer(_Width, _Height);
	CreateRasterizerState();
	CreateViewport();
	CreateProjcectionMatrix(_ScreenDepth, _ScreenNear);
}

void Device::InitalizeGPUInfo()
{
	HRESULT hr;

	IDXGIFactory* Factory;
	hr = CreateDXGIFactory(IID_PPV_ARGS(&Factory));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* Adapter;
	hr = Factory->EnumAdapters(0, &Adapter);
	assert(SUCCEEDED(hr));

	//위에랑 다른게 뭘까?

	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)&Factory);
	assert(SUCCEEDED(hr));

	hr = Factory->EnumAdapters(0, &Adapter);
	assert(SUCCEEDED(hr));

	IDXGIOutput* AdapterOutput;
	hr = Adapter->EnumOutputs(0, &AdapterOutput);
	assert(SUCCEEDED(hr));


	UINT ModeCount;
	hr = AdapterOutput->GetDisplayModeList(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&ModeCount, NULL);

	assert(SUCCEEDED(hr));

	//여기도 중복?, 배열이긴한데

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[ModeCount];

	hr = AdapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&ModeCount,
		displayModeList
	);

	assert(SUCCEEDED(hr));


	for (UINT i = 0; i < ModeCount; i++)
	{
		bool isCheck = true;

		isCheck &= displayModeList[i].Width == SCREENWIDTH;
		isCheck &= displayModeList[i].Height == SCREENHEIGHT;

		if (isCheck == true)
		{
			m_Numerator = displayModeList[i].RefreshRate.Numerator;
			m_Denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC AdapterDesc;
	hr = Adapter->GetDesc(&AdapterDesc);
	assert(SUCCEEDED(hr));



	m_MemorySize = AdapterDesc.DedicatedVideoMemory / 1024 / 1024;
	m_Description = AdapterDesc.Description;


	SafeDeleteArray(displayModeList);


	SAFE_RELEASE(AdapterOutput);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(Factory);
}

UINT Device::CreateSwapChainAndDevice()
{
	UINT Flags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE Driver_type = D3D_DRIVER_TYPE_WARP; // D3D_DRIVER_TYPE_HARDWARE;

	D3D_FEATURE_LEVEL FeatureLevel_types[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3 ,
		D3D_FEATURE_LEVEL_9_2 ,
		D3D_FEATURE_LEVEL_9_1 ,
	};

	UINT FeatureLevels = ARRAYSIZE(FeatureLevel_types);//버젼 담아둔거 갯수

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;// SwapChain의 특성을 담고 있는 구조체 
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc)); //메모리 영역을 0X00으로 채우는 매크로

	SwapChainDesc.BufferCount = 1; //BackBuffer 개수(여기서 1개)	//BufferDesc : BackBuffer의 속성 설정(구조체 형태)
	SwapChainDesc.BufferDesc.Height = SCREENHEIGHT;					//BackBuffer: 높이
	SwapChainDesc.BufferDesc.Width = SCREENWIDTH;					//BackBuffer: 가로
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//BackBuffer 픽셀 형식
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;			//화면 갱신률(분모)
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;			//화면 갱신률(분자)
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//버퍼 용도, // 렌더 타겟 출력으로 surface 또는 자원을 사용
	SwapChainDesc.OutputWindow = g_hWnd;							//렌더링 결과를 표시할 윈도우 창의 핸들
	SwapChainDesc.SampleDesc.Count = 1;								//Multisampling을 위해 추출할 표본 개수와 품질 수준을 서술하는 구조체
	SwapChainDesc.SampleDesc.Quality = 0;							
	SwapChainDesc.Windowed = TRUE;									//창모드 = true, 전체화면 = false

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,									//IDXGIAdapter 인터페이스'를 설정, NULL = 최초에 발견한 디바이스를 사용. 
		Driver_type,							//드라이버 타입
		NULL,									//소프트웨어 래스터라이저가 구현되어 있는 DLL이 핸들지정, 걍 NULL하는 걸로
		Flags,									//API 레이어
		FeatureLevel_types,						//피처레벨(지원 기능 레벨) 배열을 설정, 우선순위가 높은순으로배열
		FeatureLevels,							//위에거 개수
		D3D11_SDK_VERSION,						//사용하고 있는 DX SDK의 버전을 넘겨줍니다.
		&SwapChainDesc,							//스왑체인의 설정값들을 저장한 구조체의 포인터
		&m_pSwapChain,							//생성된 스왑체인 인터페이스의 포인터를 담을 변수
		&m_pDevice,								//생성된 디바이스 인터페이스의 포인터를 담을 변수
		&m_FeatureLevel,						//생성에 성공한 경우에는 FeatureLevel_types에서 지정했던 배열의 처음값을 return
		&m_pDeviceContext);						//생성된 디바이스 컨텍스트 인터페이스의 포인터를 담을 변수

	if (FAILED(hr))
	{
		ERROR_MESSAGE(L"D3D11CreateDevice Failed.");
		return S_FALSE;
	}

	if (m_FeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		ERROR_MESSAGE(L"Direct3D 11 을 지원하지 않음.");
		return S_FALSE;
	}

	return S_OK;
}

void Device::CreateBackBuffer(float _Width, float _Height)
{
	/*
		Back Buffer의 RenderTarget View를 생성
		Depth,Stencil Buffer 생성
		Render Target View와 Depth,Stencil View를 파이프라인에 바인딩
		ViewPort 설정
	*/

	HRESULT hr;

	ID3D11Texture2D*		m_pBackBuffer;		 //2차원 Texture를 생성용
	ID3D11RenderTargetView* m_pRenderTargetView; //렌더링 파이프라인의 출력을 받을 자원을 연결하는데 쓰인다, 색상값을 담는 버퍼를 위한것
	ID3D11DepthStencilView*	m_pDepthStencilView; //위에거랑 비슷, 깊이와 스텐실 값을 담는 버퍼를 위한것


	//GetBackBuffer And Create RTV
	{
		ID3D11Texture2D* pBackbufferPointer;

		//0번 back Buffer를 가져온다.
		hr = m_pSwapChain->GetBuffer(0,  //백버퍼 번호
			__uuidof(ID3D11Texture2D), //백버퍼에 접근하는 인터페이스
			(void **)&pBackbufferPointer); //백버퍼를 받아올 변수
		assert(SUCCEEDED(hr));

		//backbuffer Resource의 RenderTargetView 생성
		hr = GetDevice()->CreateRenderTargetView(
			pBackbufferPointer, //뷰에서 엑세스하는 리소스
			NULL,				//레더타겟 뷰의 정의
			&m_pRenderTargetView);//렌더타겟을 받아올 변수
		assert(SUCCEEDED(hr));

		//후면버퍼를 다 사용했기 때문에 Release 호출
		SAFE_RELEASE(pBackbufferPointer);
	}

	//Create Texture - DSV
	{
		D3D11_TEXTURE2D_DESC Desc = { 0 };
		Desc.Width = (UINT)_Width; // 텍스쳐의 너비(텍셀)
		Desc.Height = (UINT)_Height;// 텍스쳐의 높이(텍셀)
		Desc.MipLevels = 1; // 뎁스 버퍼는 밉맵수준이 하나만 있으면 된다.
		Desc.ArraySize = 1; // 텍스쳐 배열의 개수 뎁스 버퍼는  1개면 된다.
		Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //텍셀의 포맷, DXGI_FORMAT_D24_S8 과 같은 형식
		Desc.SampleDesc.Count = 1; // Multi Sampling 정보와 같아야 함.
		Desc.SampleDesc.Quality = 0; // Multi Sampling 정보와 같아야 함.
		Desc.Usage = D3D11_USAGE_DEFAULT; //텍스쳐의 용도에 따른 필드, CPU(Dynamic, Staging), GPU(DEFAULT, IMMUTABLE)
		Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 자원이 파이프라인에 어떤식으로 묶일지 정의 Shader_Resource, Redner_Target
		Desc.CPUAccessFlags = 0;  // Usage가 DYANMIC or STAGING, Usage에서 DYNAMIC이나 STAGING의 경우 CPU <-> GPU 메모리간의 전송이 있어야하므로 성능상 저하가 심하므로 꼭 필요한 경우에만 사용한다.
		Desc.MiscFlags = 0; // 기타 플래그

		hr = m_pDevice->CreateTexture2D(
			&Desc,						// 생성할 텍스쳐를 서술하는 구조체		
			NULL, 						//
			&m_pBackBuffer);			//깊이, 스텐실 버퍼를 가리키는 포인터를 돌려준다.
		assert(SUCCEEDED(hr));
	}


	{
		D3D11_DEPTH_STENCIL_DESC Desc;
		ZeroMemory(&Desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

		Desc.DepthEnable = true; //깊이 테스트 활성화
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //쓰기
		Desc.DepthFunc = D3D11_COMPARISON_LESS;//앞쪽물체를 렌더
		Desc.StencilEnable = true; //스텐실 테스트
		Desc.StencilReadMask = 0xFF; //스텐실 읽기
		Desc.StencilWriteMask = 0xFF;//스텐실 쓰기

		//면이 앞을보는 경우 스텐실 테스트 설정
		Desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		Desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		Desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		Desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		
		//면이 뒤를보는 경우 스텐실 테스트 설정
		Desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		Desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		Desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		Desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		hr = m_pDevice->CreateDepthStencilState(&Desc, &m_pDepthStencilState);
		assert(SUCCEEDED(hr));
	}
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);//스텐실 테스트에서 사용할 찬조값



	//Create DSV
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC Desc;
		ZeroMemory(&Desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		Desc.Texture2D.MipSlice = 0;

		hr = m_pDevice->CreateDepthStencilView(
			m_pBackBuffer,					////생성한 텍스쳐 포인터
			&Desc,							// DepthStenCilView Descrption 포인터, 뎁스 스텐실 버퍼를 생성할 때 형식을 지정했으면 NULL값으로 지정해 줘도 된다. 
			&m_pDepthStencilView);			//생성한 DepthStencilView 반환

		//렌더 타겟설정, 뷰 개수, 렌더타겟뷰 + 깊이스텐실뷰
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	}
}

void Device::CreateRasterizerState()
{
	HRESULT hr;

	//** Create Rasterizer desc
	//레스트라이저의 동작은 레스트라이저 스테이트에서 설정(위에것들도 마찬가지)
	{
		D3D11_RASTERIZER_DESC Desc;

		Desc.AntialiasedLineEnable = false;//라인 안티엘리어싱
		Desc.CullMode = D3D11_CULL_BACK;//컬모드(보이지 않는것 그리지 않기)
		Desc.DepthBias = 0;// 깊이 바이어스, 실제 z값에 더해질 바이어스 값 설정
		Desc.DepthBiasClamp = 0.0f;
		Desc.DepthClipEnable = true;
		Desc.FillMode = D3D11_FILL_SOLID; //와이어 프레임을 할 것인가
		Desc.FrontCounterClockwise = false;//어느쪽을 앞면으로 할 것인가, 시계방향이 뒷면
		Desc.MultisampleEnable = false; //멀티 샘플링에 의한 안티엘리어싱
		Desc.ScissorEnable = false;//시저 테스트
		Desc.SlopeScaledDepthBias = 0.0f;

		hr = m_pDevice->CreateRasterizerState(
			&Desc, &m_pRasterizerState);
		assert(SUCCEEDED(hr));

		m_pDeviceContext->RSSetState(m_pRasterizerState);
	}
}

void Device::CreateViewport()
{
	//뷰포트 설정
	D3D11_VIEWPORT Viewport;
	//변환공식
	/*
		X = (x+1) * Viewport.Width * 0.5 + Viewport.TopLeftX
		Y = (1-y) * Viewport.Height * 0.5 + Viewport.TopLeftY
		Z = Viewport.MinDepth + z * (Viewport.MaxDepth – Viewport.MinDepth)
	*/
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = SCREENWIDTH;
	Viewport.Height = SCREENHEIGHT;
	Viewport.MinDepth = 0;
	Viewport.MaxDepth = 1;

	m_pDeviceContext->RSSetViewports(1, &Viewport);
}

void Device::CreateProjcectionMatrix(float _ScreenDepth, float _ScreenNear)
{
	FieldOfView = (float)XM_PI / 4.0f;
	ScreenAspect = (float)SCREENWIDTH / (float)SCREENHEIGHT;

	//원근법(정사영)
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(FieldOfView, ScreenAspect, _ScreenDepth, _ScreenNear);

	m_WorldMatrix = DirectX::XMMatrixIdentity();

	//정투영법
	m_OrthoMatrix = XMMatrixOrthographicLH((float)SCREENWIDTH, (float)SCREENHEIGHT,_ScreenNear, _ScreenDepth);
}

void Device::ResizeScreen(float _width, float _height)
{
	if (_width < 1 || _height < 1 || 
		_height > 1080 || _width > 1920)
		return;

	m_ScreenSize.Width = _width;
	m_ScreenSize.Height = _height;

	ReleaseBackBuffer();

	HRESULT hr = m_pSwapChain->ResizeBuffers(
		0, (UINT)_width, (UINT)_height, 
		DXGI_FORMAT_UNKNOWN, 0);

	assert(SUCCEEDED(hr));

	CreateBackBuffer(_width, _height);
}

void Device::BeginPaint(
	float _Red, float _Green, float _Blue, float _Alpha)
{
	float ClearColor[4] = { _Red, _Green, _Blue, _Alpha };

	m_pDeviceContext->ClearRenderTargetView(
		m_pRenderTargetView, ClearColor);

	m_pSwapChain->Present(0, 0);
}

void Device::EndPaint()
{
	if (m_VSYNCEnabled)
	{ // 새로고침 비율을 고정합니다. 
		m_pSwapChain->Present(1, 0);
	}
	else
	{ // 가능한 한 빠르게 표시합니다. 
		m_pSwapChain->Present(0, 0);
	}
}

void Device::GetVideoCardInfo(char* _CardName, int& _Memory)
{
	strcpy_s(_CardName, 128, m_VideoCardDescription);
	_Memory = m_VideoCardMemory;
}

void Device::ShutDown()
{
	if (m_pSwapChain)
		m_pSwapChain->SetFullscreenState(false, NULL);

	if (m_pRasterizerState)
		SAFE_RELEASE(m_pRasterizerState);

	if (m_pDepthStencilView)
		SAFE_RELEASE(m_pDepthStencilView);

	if (m_pDepthStencilState)
		SAFE_RELEASE(m_pDepthStencilState);

	if (m_pDepthStencilBuffer)
		SAFE_RELEASE(m_pDepthStencilBuffer);

	if (m_pRenderTargetView)
		SAFE_RELEASE(m_pRenderTargetView);

	if (m_pDeviceContext)
		SAFE_RELEASE(m_pDeviceContext);

	if (m_pDevice)
		SAFE_RELEASE(m_pDevice);

	if (m_pSwapChain)
		SAFE_RELEASE(m_pSwapChain);
}

void Device::ReleaseBackBuffer()
{
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pBackBuffer);
}