#pragma once
#include "Headers.h"
#include <fstream>


class ColorShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX World;
		XMMATRIX View;
		XMMATRIX Projection;
	};
private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
public:
	UINT Initialize();
	UINT Render(int, XMMATRIX, XMMATRIX, XMMATRIX);
	void Release();
private:
	UINT InitializeShader(LPCWSTR, LPCWSTR);
	void OutputShaderErrorMessage(ID3D10Blob*, LPCWSTR);
	bool SetShaderParameters(XMMATRIX&, XMMATRIX&, XMMATRIX&);
public:
	ColorShader();
	~ColorShader();
};

