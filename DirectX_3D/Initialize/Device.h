#pragma once
#include "Headers.h"

class Device
{
public:
	DECLARE_SINGLETON(Device)
private:
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pDeviceContext = nullptr;
	IDXGISwapChain*			m_pSwapChain = nullptr;
	D3D_FEATURE_LEVEL		m_FeatureLevel;

	UINT	m_MemorySize;
	UINT	m_Numerator;
	UINT	m_Denominator;

	wstring	m_Description;

	ID3D11Texture2D*		m_pBackBuffer;
	ID3D11DepthStencilView*	m_pDepthStencilView;
	ID3D11RenderTargetView*	m_pRenderTargetView;

	ID3D11DepthStencilState*	m_pDepthStencilState;
	ID3D11RasterizerState* m_pRasterizerState;
	ID3D11Texture2D* m_pDepthStencilBuffer;

	//** ±¸Á¶Ã¼
	SCREENSCALE m_ScreenSize;

	bool BufferChanging;
	bool m_VSYNCEnabled;

	float FieldOfView, ScreenAspect;
	int m_VideoCardMemory;
	char m_VideoCardDescription[128];

	XMMATRIX m_WorldMatrix, m_OrthoMatrix, m_ProjectionMatrix;
public:
	void SetGPUInfo();
	UINT CreateSwapChainAndDevice();
	void CreateBackBuffer(float _Width, float _Height);
public:
	void CreateRasterizerState();
	void CreateViewport();

	void CreateProjcectionMatrix(float _ScreenDepth, float _ScreenNear);
	void ResizeScreen(float _width, float _height);
public:
	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }
	IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }

private:
	Device();
	~Device();
};

