#include "MainUpdate.h"



int main(void)
{
	MainUpdate Main;
	Main.Initialize();

	ULONGLONG Time = GetTickCount64();


	while (true)
	{
		if (Time < GetTickCount64())
		{
			Time = GetTickCount64();
			system("cls");


			Main.Update();
			Main.Render();
		}
	}

	return 0;
}