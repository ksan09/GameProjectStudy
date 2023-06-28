#include "pch.h"
#include "console.h"
#include "IntroScene.h"
#include "SceneManager.h"

IntroScene::IntroScene()
{
	startIdx = 0;
	maxIdx = 0;
}

IntroScene::~IntroScene()
{
}

void IntroScene::Init()
{
	startIdx = 0;
	maxIdx = 2;
	TitleRender();
}

void IntroScene::Update(float dt)
{
	char ch = _getch();
	switch (ch)
	{
	case 'w':
	case 'W':
	{
		PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
		if (startIdx == 0) return;
		startIdx--;
	}
	break;
	case 's':
	case 'S':
	{
		PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
		if (startIdx == maxIdx) return;
		startIdx++;
	}
	break;
	case ' ':
	{
		PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
		if (startIdx == 0)
		{
			GET_SINGLE(SceneManager)->LoadScene(L"IngameScene");
		}
		else if (startIdx == 1)
		{
			// 설명 씬 추가
			GET_SINGLE(SceneManager)->LoadScene(L"ExplainScene");
		}
		else if (startIdx == 2)
		{
			// 나가기
			exit(0);
		}
	}
	break;
	default:
		break;
	}
}

void IntroScene::Render()
{
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);

	wstring PlayUIText[3] = {
		L"   ╔═╗┬  ┌─┐┬ ┬                  ",
		L"   ╠═╝│  ├─┤└┬┘                 ",
		L"   ╩  ┴─┘┴ ┴ ┴                   ",
	};
	SelectUIRender((startIdx == 0), 15, PlayUIText);
	wstring ExplainUIText[3] = {
		L"   ╔═╗─┐ ┬┌─┐┬  ┌─┐┬┌┐┌       ",
		L"   ║╣ ┌┴┬┘├─┘│  ├─┤││││      ",
		L"   ╚═╝┴ └─┴  ┴─┘┴ ┴┴┘└┘        ",
	};
	SelectUIRender((startIdx == 1), 20, ExplainUIText);
	wstring ExitUIText[3] = {
		L"   ╔═╗─┐ ┬┬┌┬┐                  ",  
		L"   ║╣ ┌┴┬┘│ │                    ",
		L"   ╚═╝┴ └─┴ ┴                     ",  
	};
	SelectUIRender((startIdx == 2), 25, ExitUIText);
	
	iCurmode = _setmode(_fileno(stdout), _O_TEXT);
}

void IntroScene::TitleRender()
{
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	GoToxy(0, 1);
	SetColor((int)COLOR::BLACK, (int)COLOR::LIGHT_GRAY);
	wcout << L"                                                                                                                      " << '\n';
	wcout << L"     __   __  _______  ___      ___      _______    ______   __   __  __    _  _______  _______  _______  __    _     " << '\n';
	wcout << L"    |██| |██||███████||███|    |███|    |███████|  |      | |  | |  ||  |  | ||       ||       ||       ||  |  | |    " << '\n';
	wcout << L"    |██|_|██||███████||███|    |███|    |███████|  |  _    ||  | |  ||   |_| ||    ___||    ___||   _   ||   |_| |    " << '\n';
	wcout << L"    |███████||███|___ |███|    |███|    |██| |██|  | |█|   ||  |_|  ||       ||   | __ |   |___ |  |█|  ||       |    " << '\n';
	wcout << L"    |███████||███████||███|___ |███|___ |██|_|██|  | |█|   ||       ||  _    ||   ||  ||    ___||  |█|  ||  _    |    " << '\n';
	wcout << L"    |███████||███|___ |███████||███████||███████|  |       ||       || | |   ||   |_| ||   |___ |       || | |   |    " << '\n';
	wcout << L"    |██| |██||███████||███████||███████||███████|  |______| |_______||_|  |__||_______||_______||_______||_|  |__|    " << '\n';
	wcout << L"                                                                                                                      " << '\n';
	SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
	iCurmode = _setmode(_fileno(stdout), _O_TEXT);
}

void IntroScene::SelectUIRender(bool select, int posY, wstring str[3])
{
	GoToxy(0, posY);
	if(select == true) SetColor((int)COLOR::LIGHT_YELLOW, (int)COLOR::BLACK);
	for (int i = 0; i < 3; ++i)
	{
		if (select && i == 1)
		{
			GoToxy(0, posY + i);
			wcout << L"  >";
		}
		else if (select) GoToxy(3, posY + i);
		wcout << str[i] << '\n';
	}
	if (select == true) SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
}
