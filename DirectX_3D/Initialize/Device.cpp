#include "Device.h"

Device::Device()
{
	SetGPUInfo();
	CreateSwapChainAndDevice();


}

Device::~Device()
{

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

	UINT FeatureLevels = ARRAYSIZE(FeatureLevel_types);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));

	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Height = SCREENHEIGHT;
	SwapChainDesc.BufferDesc.Width = SCREENWIDTH;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = g_hWnd;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = TRUE;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		Driver_type,
		NULL,
		Flags,
		FeatureLevel_types,
		FeatureLevels,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		&m_pSwapChain,
		&m_pDevice,
		&m_FeatureLevel,
		&m_pDeviceContext);

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
	HRESULT hr;
	
	ID3D11Texture2D*		m_pBackBuffer;
	ID3D11DepthStencilView*	m_pDepthStencilView;
	ID3D11RenderTargetView* m_pRenderTargetView;

	//GetBackBuffer And Create RTV
	{
		ID3D11Texture2D* pBackbufferPointer;

		hr = m_pSwapChain->GetBuffer(0, 
			__uuidof(ID3D11Texture2D), (void **)&pBackbufferPointer);
		assert(SUCCEEDED(hr));

		hr = GetDevice()->CreateRenderTargetView(
			pBackbufferPointer, NULL, &m_pRenderTargetView);
		assert(SUCCEEDED(hr));

		SAFE_RELEASE(pBackbufferPointer);
	}

	//Create Texture - DSV
	{
		D3D11_TEXTURE2D_DESC Desc = { 0 };
		Desc.Width = (UINT)_Width;
		Desc.Height = (UINT)_Height;
		Desc.MipLevels = 1;
		Desc.ArraySize = 1;
		Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.Usage = D3D11_USAGE_DEFAULT;
		Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		Desc.CPUAccessFlags = 0;
		Desc.MiscFlags = 0;

		hr = m_pDevice->CreateTexture2D(&Desc, NULL, &m_pBackBuffer);
		assert(SUCCEEDED(hr));
	}


	{
		D3D11_DEPTH_STENCIL_DESC Desc;
		ZeroMemory(&Desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = true;
		Desc.StencilReadMask = 0xFF;
		Desc.StencilWriteMask = 0xFF;

		Desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		Desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		Desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		Desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		Desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		Desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		Desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		Desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		hr = m_pDevice->CreateDepthStencilState(&Desc, &m_pDepthStencilState);
		assert(SUCCEEDED(hr));
	}
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);



	//Create DSV
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC Desc;
		ZeroMemory(&Desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		Desc.Texture2D.MipSlice = 0;

		hr = m_pDevice->CreateDepthStencilView(
			m_pBackBuffer, &Desc, &m_pDepthStencilView);
		assert(SUCCEEDED(hr));

		//SetRenderTarget(m_pRenderTargetView, m_pDepthStencilView);
	}
}

void Device::CreateRasterizerState()
{
	HRESULT hr;

	//** Create Rasterizer desc
	{
		D3D11_RASTERIZER_DESC Desc;

		Desc.AntialiasedLineEnable = false;
		Desc.CullMode = D3D11_CULL_BACK;
		Desc.DepthBias = 0;
		Desc.DepthBiasClamp = 0.0f;
		Desc.DepthClipEnable = true;
		Desc.FillMode = D3D11_FILL_SOLID;
		Desc.FrontCounterClockwise = false;
		Desc.MultisampleEnable = false;
		Desc.ScissorEnable = false;
		Desc.SlopeScaledDepthBias = 0.0f;

		hr = m_pDevice->CreateRasterizerState(
			&Desc, &m_pRasterizerState);
		assert(SUCCEEDED(hr));

		m_pDeviceContext->RSSetState(m_pRasterizerState);
	}
}

void Device::CreateViewport()
{
	D3D11_VIEWPORT Viewport;

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

	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(FieldOfView, ScreenAspect, _ScreenDepth, _ScreenNear);

	m_WorldMatrix = DirectX::XMMatrixIdentity();

	m_OrthoMatrix = XMMatrixOrthographicLH((float)SCREENWIDTH, (float)SCREENHEIGHT,_ScreenNear, _ScreenDepth);
}

void Device::ResizeScreen(float _width, float _height)
{
	if (_width < 1 || _height < 1 || _height > 1080 || _width > 1920)
		return;

	m_ScreenSize.Width = _width;
	m_ScreenSize.Height = _height;

	//ReleaseBackBuffer();

	HRESULT hr = m_pSwapChain->ResizeBuffers(
		0, (UINT)_width, (UINT)_height, DXGI_FORMAT_UNKNOWN, 0);
	assert(SUCCEEDED(hr));

	CreateBackBuffer(_width, _height);
}

void Device::SetGPUInfo()
{
	//** 그래픽 장치의 정보를 받아옴.
	Microsoft::WRL::ComPtr<IDXGIFactory> Factory;
	Microsoft::WRL::ComPtr<IDXGIAdapter> Adapter;

	HRESULT hr;
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
			m_Denominator =displayModeList[i].RefreshRate.Denominator;
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

