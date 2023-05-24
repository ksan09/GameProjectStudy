#pragma once
#include <Windows.h>

enum class COLOR
{
	BLACK, BLUE, GREEN, SKYBLUE, RED,
	VIOLET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
	LIGHT_GRREN, MINT, LIGHT_RED, LIGHT_VIOLET,
	LIGHT_YELLOW, WHITE
};

void FullScreen();
void GoToxy(int, int);
BOOL GoToxyTest(int, int);
void CursorSet(bool, DWORD);
void SetColor(int, int);
int GetColor();
int GetBGColor();
void Fontsize(UINT _weight, UINT _sizex, UINT _sizey);