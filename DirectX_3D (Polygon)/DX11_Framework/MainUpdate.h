#pragma once
#include "Headers.h"

class Model;
class ColorShader;
class Camera;
class MainUpdate
{
private:
	HDC m_hdc;
	Model* m_Model;
	ColorShader* m_ColorShader;
	Camera* m_Camera;
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
public:
	MainUpdate();
	~MainUpdate();
};

