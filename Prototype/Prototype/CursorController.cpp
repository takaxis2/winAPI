#include "CursorController.h"


CursorController::CursorController()
{

}

CursorController::~CursorController()
{

}

void CursorController::SetCursorPosition(int _ix, int _iy, char* str, int _Color)
{
	COORD Pos;
	Pos.X = _ix;
	Pos.Y = _iy;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);
	printf("%s", str);
}

void CursorController::SetCursorPosition(int _ix, int _iy, int _value, int _Color)
{
	COORD Pos;
	Pos.X = _ix;
	Pos.Y = _iy;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);



	char* string = (char*)malloc(sizeof(char) * 10);
	_itoa(_value, string, 10);

	printf("%s", string);
}
void CursorController::SetCursorHide()
{
	HANDLE HCursor = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 100;
	Info.bVisible = FALSE;
	SetConsoleCursorInfo(HCursor, &Info);
}

void CursorController::SetColor(int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}