#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "console.h"

using namespace std;

int main()
{
	clock_t oldTime, crtTime;
	oldTime = clock();
	while (true)
	{
		crtTime = clock();
		if (crtTime - oldTime >= 1000) 
		{
			cout << "1초가 지났다." << '\n';
			oldTime = crtTime;
		}

	}


	/*
	int a;
	while (true)
	{
		cin >> a;
		if (cin.fail())
		{
			cout << "님 비정상 입력." << '\n';
			cin.clear();
			cin.ignore(1024, '\n');
		}
		cout << a << '\n';
	}
	*/
}

/*
int main()
{
	SetConsoleTitle(TEXT("2-3 Bombman"));

	HWND hConsole = GetConsoleWindow();
	SetWindowLong(hConsole, GWL_STYLE, 
		GetWindowLong(hConsole, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	RECT rect;
	GetWindowRect(hConsole, &rect);

	int test;
	int x = 0, y = 0;
	int beforeX = 0, beforeY = 0;
	while (true)
	{
		if (_kbhit())
		{
			BOOL test = GoToxyTest(x, y);
			if (test == FALSE)
			{
				x = beforeX;
				y = beforeY;
				continue;
			}
			else
			{
				beforeX = x;
				beforeY = y;
			}

			_putch('a');

			if (GetAsyncKeyState(VK_UP)    & 0x8000) y--;
			if (GetAsyncKeyState(VK_DOWN)  & 0x8000) y++;

			if (GetAsyncKeyState(VK_LEFT)  & 0x8000) x--;
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) x++;
			Sleep(50);

		}	
	}

	char a = _getch();
}
*/