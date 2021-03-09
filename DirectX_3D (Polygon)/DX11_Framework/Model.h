#pragma once
#include "Headers.h"

class Model
{
private:
	struct VertexType
	{
		XMFLOAT3 Position;
		XMFLOAT4 Color;
	};
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	int m_VertexCount;
	int m_IndexCount;
public:
	UINT Initialize();
	void Update();
	void Release();
public:
	UINT InitBuffers();
	int GetIndexCount() { return m_IndexCount; }

public:
	Model();
	~Model();
};

