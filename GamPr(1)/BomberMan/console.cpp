#include "console.h"

void FullScreen()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleDisplayMode(hOut,
		 CONSOLE_FULLSCREEN_MODE, NULL);
}

void GoToxy(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cur = { x, y };

	SetConsoleCursorPosition(hOut, Cur);
}

BOOL GoToxyTest(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cur = { x, y };

	return SetConsoleCursorPosition(hOut, Cur);
}

void CursorSet(bool _bVis, DWORD _dwSize)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Curinfo;
	Curinfo.bVisible = _bVis;
	Curinfo.dwSize = _dwSize;

	SetConsoleCursorInfo(hOut, &Curinfo);
}

void SetColor(int _color, int _bgColor)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hOut, (_bgColor<<4) | _color);
}

int GetColor()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(hOut, &info);
	int color = info.wAttributes & 0xf;
	return color;
}

int GetBGColor()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(hOut, &info);
	int color = (info.wAttributes & 0xf) >> 4;
	return color;
}
