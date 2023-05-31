#include <iostream>
#include "Core.h"
#include "MapManager.h"
#include "console.h"
using namespace std;


Core* Core::m_pInst = nullptr;

Core::Core()
{
}

Core::~Core()
{
}

bool Core::Init()
{
	MapManager::GetInst()->Init();
	system("mode con cols=80 lines=30");
	CursorSet(false, 1);
	return true;
}

void Core::Run()
{
	int iStage = MenuDraw();

	// ¸Ê ±×·ÁÁÖ±â
	MapManager::GetInst()->Run(iStage - 1);
}

int Core::MenuDraw()
{
	cout << "1. Stage 1" << '\n';
	cout << "2. Stage 2" << '\n';
	cout << "3. Stage 3" << '\n';
	cout << "4. Exit" << '\n';

	int iInput;
	cin >> iInput;

	return iInput;
}
