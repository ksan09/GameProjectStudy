#include <iostream>
#include "pch.h"
#include "Define.h"
#include "console.h"
#include "GameLogic.h"
#include "SceneManager.h"
#include "IngameScene.h"
#include "IntroScene.h"
#include "ExplainScene.h"

using namespace std;

int main()
{
	CursorSet(false, NULL);
	GameLogic game = GameLogic();

	// 씬 미리 등록
	GET_SINGLE(SceneManager)->RegisterScene(L"IntroScene", make_shared<IntroScene>());
	GET_SINGLE(SceneManager)->RegisterScene(L"IngameScene", make_shared<IngameScene>());
	GET_SINGLE(SceneManager)->RegisterScene(L"ExplainScene", make_shared<ExplainScene>());

	// 현재 씬 로드
	GET_SINGLE(SceneManager)->LoadScene(L"IntroScene");

	game.Init();
	while (true)
	{
		game.Render();
		game.Update();
	}
}