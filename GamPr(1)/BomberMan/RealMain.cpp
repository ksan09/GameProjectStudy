#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <vector>

#include "console.h"
#include "StartScene.h"
#include "GameLogic.h"
#include "resource.h"

using namespace std;

int main()
{
	char			cMaze[VERTICAL][HORIZON] = {};
	PLAYER			tPlayer = {};
	POS				tStartpos = {};
	POS				tEndpos = {};

	vector<BOOM>	vecBomb;
	vector<POS>		boomEffect;

	Init(cMaze, &tPlayer, &tStartpos, &tEndpos);

	// 시작씬 제작
	while (true)
	{
		system("cls");
		GameTitle();
		int menu = DrawMenu();
		if (menu == 1)
			break;
		else if (menu == 2)
			GameInfo();
		else if (menu == 3)
		{
			// 게임 종료
			cout << " 게임을 종료합니다." << '\n';
			for (int i = 0; i < 3; ++i)
			{
				cout << '\r' << 3 - i << "...";
				Sleep(1000);
			}
			return 0;
		}
		Sleep(50);

	}
	system("cls");
	// 게임 로직..

	while (true)
	{
		GoToxy(0, 0);
		Update(cMaze, &tPlayer, vecBomb, boomEffect);
		Render(cMaze, &tPlayer, boomEffect);
		// 내가 이동하다가 도착점에 도착하면
		// 클리어 소리

		if (tPlayer.tpos == tEndpos)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE1),
				NULL, SND_RESOURCE | SND_SYNC);
		}
	}
}