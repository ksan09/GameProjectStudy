#include <iostream>
#include "pch.h"
#include "Define.h"
#include "console.h"
#include "GameLogic.h"
#include "SceneManager.h"
#include "IngameScene.h"

using namespace std;

int main()
{
	GameLogic game = GameLogic();

	// 씬 미리 등록
	GET_SINGLE(SceneManager)->RegisterScene(L"IngameScene", make_shared<IngameScene>());

	// 현재 씬 로드
	GET_SINGLE(SceneManager)->LoadScene(L"IngameScene");

	game.Init();
	while (true)
	{
		game.Update();
		game.Render();
	}
}