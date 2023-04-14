#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <Windows.h>
#include "StartScene.h"
#include "console.h"
#include "GameLogic.h"

using namespace std;

void GameTitle()
{
	GoToxy(0, 1);
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	//임시 타이틀 - 나중에 봄브맨으로 바꾸기
	
	wcout << L"██████╗  ██████╗ ███╗   ███╗██████╗ ███████╗██████╗     ███╗   ███╗ █████╗ ███╗   ██╗" << '\n';
	wcout << L"██╔══██╗██╔═══██╗████╗ ████║██╔══██╗██╔════╝██╔══██╗    ████╗ ████║██╔══██╗████╗  ██║" << '\n';
	wcout << L"██████╔╝██║   ██║██╔████╔██║██████╔╝█████╗  ██████╔╝    ██╔████╔██║███████║██╔██╗ ██║" << '\n';
	wcout << L"██╔══██╗██║   ██║██║╚██╔╝██║██╔══██╗██╔══╝  ██╔══██╗    ██║╚██╔╝██║██╔══██║██║╚██╗██║" << '\n';
	wcout << L"██████╔╝╚██████╔╝██║ ╚═╝ ██║██████╔╝███████╗██║  ██║    ██║ ╚═╝ ██║██║  ██║██║ ╚████║" << '\n';
	wcout << L"╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝" << '\n';

	iCurmode = _setmode(_fileno(stdout), O_TEXT);

	
}

int KeyController()
{
	int iInput = _getch();
	if (iInput == 224)
	{
		iInput = _getch();

		switch (iInput)
		{
		case 72:
			return (int)KEY::UP;
		case 80:
			return (int)KEY::DOWN;
		default:
			break;
		}
	}
	else if (iInput == 32)
	{
		return (int)KEY::SPACEBAR;
	}


	return -1;
}

void GameInfo()
{
	system("cls");
	cout << "\n\n";
	cout << "|  조작법 |" << '\n';
	cout << "메뉴 이동 : Up, Down" << '\n';
	cout << "메뉴 선택 : Space" << '\n';
	cout << "플레이어 이동 : 뱡향키" << '\n';
	cout << "폭탄 설치 : Space" << '\n';
	cout << "푸시능력 ON/OFF : E" << '\n';
	cout << '\n';
	cout << "나가기 (SPACE)" << '\n';
	while (KeyController() != (int)KEY::SPACEBAR);
}

int DrawMenu()
{
	int x = 30, y = 12;

	string screenSelectVal[3] =
	{
		"게임 시작",
		"게임 정보",
		"게임 종료"
	};

	for (int i = 0; i < 3; ++i)
	{
		GoToxy(x, y + i);
		cout << screenSelectVal[i];
	}

	static int currentPos = 0;

	// 키 입력 받아 >(꺽쇠) 이동
	while (true)
	{
		int key = KeyController();
		switch (key)
		{
		case (int)KEY::UP:
		{
			cout << "\b ";
			currentPos--;
			if (currentPos < 0) currentPos = 0;
			GoToxy(x - 2, y + currentPos);
			cout << ">";
		}
		break;
		case (int)KEY::DOWN:
		{
			cout << "\b ";
			currentPos++;
			if (currentPos > 2) currentPos = 2;
			GoToxy(x - 2, y + currentPos);
			cout << ">";
		}
		break;
		case (int)KEY::SPACEBAR:
		{
			return currentPos + 1;
		}
		break;
		default:
			break;
		}
	}
	return -1;
}
