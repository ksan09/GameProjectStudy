#include "pch.h"
#include "console.h"
#include "ClearScene.h"
#include "SceneManager.h"

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Init()
{
}

void ClearScene::Update(float dt)
{
	while (true)
	{
		char inputCh = _getch();
		if (inputCh == ' ')
		{
			PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
			GET_SINGLE(SceneManager)->LoadScene(L"IntroScene");
			break;
		}
	}
}

void ClearScene::Render()
{
	GoToxy(0, 3);
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L"    ╔═╗╔═╗╔╦╗╔═╗  ╔═╗╦  ╔═╗╔═╗╦═╗    " << '\n';
	wcout << L"    ║ ╦╠═╣║║║║╣   ║  ║  ║╣ ╠═╣╠╦╝    " << '\n';
	wcout << L"    ╚═╝╩ ╩╩ ╩╚═╝  ╚═╝╩═╝╚═╝╩ ╩╩╚═    " << '\n';
	iCurmode = _setmode(_fileno(stdout), O_TEXT);
	GoToxy(5, 10);
	cout << "축하합니다! 당신은 모든 적을 쓰러트리셨습니다!";

	GoToxy(8, 25);
	cout << "Spcae를 누르면 처음 화면으로 돌아갑니다.";
}
