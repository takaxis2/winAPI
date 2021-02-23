#include "Logo.h"
#include "SceneManager.h"


Logo::Logo()
{

}

Logo::~Logo()
{

}


void Logo::Initialize()
{
	cout << "Logo::Initialize" << endl;
}

void Logo::Update()
{
	cout << "Logo::Update" << endl;

	if (GetAsyncKeyState(VK_UP))
	{
		GET_SINGLE(SceneManager)->SetScene(SCENEID_MENU);
	}
}

void Logo::Render()
{
	cout << "Logo::Render" << endl;
}

void Logo::Release()
{
	cout << "Logo::Release" << endl;
}
