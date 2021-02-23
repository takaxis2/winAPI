#pragma once
#include "Headers.h"


class Scene;
class SceneManager
{
private:
	//** �� �ڽ��� �����ϱ� ����.
	static SceneManager* m_pInstance;
public:
	//** �� �ڽſ��� �����ϱ� ����.
	static SceneManager* GetInstance()
	{
		//** ���࿡ �� �ڽ��� ���ٸ�..
		if (m_pInstance == NULL)
			//** ���� �����Ҵ� ����.
			m_pInstance = new SceneManager;

		//** �׸��� �� �ڽ��� ��ȯ.
		return m_pInstance;
	}

private:
	Scene* m_pSceneState; //** ���� ���� ����
public:
	//** �� ���� �Լ�.
	void SetScene(SCENEIDS _SceneID);
	void Update(void);
	void Render(HDC _hdc);
private:
	SceneManager();
public:
	~SceneManager();
};
