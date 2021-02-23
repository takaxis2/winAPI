#include "Menu.h"
#include "SceneManager.h"


Menu::Menu()
{

}

Menu::~Menu()
{

}


void Menu::Initialize()
{
	cout << "Menu::Initialize" << endl;
}

void Menu::Update()
{
	cout << "Menu::Update" << endl;

	if (GetAsyncKeyState(VK_UP))
	{
		GET_SINGLE(SceneManager)->SetScene(SCENEID_STAGE);
	}
}

void Menu::Render()
{
	cout << "Menu::Render" << endl;
}

void Menu::Release()
{
	cout << "Menu::Release" << endl;
}
