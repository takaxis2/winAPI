#pragma once
#include "Headers.h"

class Scene;
class SceneManager
{
public:
	DECLARE_SINGLETON(SceneManager);
private:
	Scene* SceneState;
public:
	void SetScene(SCENEIDS _SceneID);
	void Update();
	void Render();
	void Release();
private:
	SceneManager();
public:
	~SceneManager();
};

