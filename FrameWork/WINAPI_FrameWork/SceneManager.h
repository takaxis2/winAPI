#pragma once
#include "Headers.h"


class Scene;
class SceneManager
{
private:
	//** 나 자신을 생성하기 위함.
	static SceneManager* m_pInstance;
public:
	//** 나 자신에게 접근하기 위함.
	static SceneManager* GetInstance()
	{
		//** 만약에 나 자신이 없다면..
		if (m_pInstance == NULL)
			//** 나를 동적할당 해줌.
			m_pInstance = new SceneManager;

		//** 그리고 나 자신을 반환.
		return m_pInstance;
	}

private:
	Scene* m_pSceneState; //** 현재 씬의 상태
public:
	//** 씬 제어 함수.
	void SetScene(SCENEIDS _SceneID);
	void Update(void);
	void Render(HDC _hdc);
private:
	SceneManager();
public:
	~SceneManager();
};
