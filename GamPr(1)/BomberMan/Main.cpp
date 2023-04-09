#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "console.h"

using namespace std;

int main()
{
	SetConsoleTitle(TEXT("2-3 Bombman"));

	int test;
	int x = 0, y = 0;
	while (true)
	{
		if (_kbhit())
		{
			GoToXY(x, y);
			_putch('a');
			if (y != 0  && GetAsyncKeyState(VK_UP)    & 0x8000) y--;
			if (y != 20 && GetAsyncKeyState(VK_DOWN)  & 0x8000) y++;

			if (x != 0  &&  GetAsyncKeyState(VK_LEFT)  & 0x8000) x--;
			if (x != 100 && GetAsyncKeyState(VK_RIGHT) & 0x8000) x++;
			Sleep(50);

			/*test = _getch();
			if (test == 224)
			{
				test = _getch();
				switch (test)
				{
				case 72:
					y--;
					break;
				case 75:
					x--;
					break;
				case 77:
					x++;
					break;
				case 80:
					y++;
					break;
				default:
					break;
				}
			}*/
		}	
	}

	char a = _getch();
}