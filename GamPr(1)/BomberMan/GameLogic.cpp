#include <iostream>
#include <Windows.h>
#include "GameLogic.h"
#include "console.h"

using namespace std;

void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pStartpos, PPOS _pEndpos)
{
	SetConsoleTitle(TEXT("2-3 Bombman"));
	CursorSet(false, 1);

	strcpy_s(_cMaze[0],  "21111100000000000000" );
	strcpy_s(_cMaze[1],  "00000111111111001000" );
	strcpy_s(_cMaze[2],  "00000100000001001000" );
	strcpy_s(_cMaze[3],  "00000100000001001000" );
	strcpy_s(_cMaze[4],  "00000100011111111000" );
	strcpy_s(_cMaze[5],  "01111100000000010000" );
	strcpy_s(_cMaze[6],  "01000100000000010000" );
	strcpy_s(_cMaze[7],  "01000100000000000000" );
	strcpy_s(_cMaze[8],  "01111111111111111113" );
	strcpy_s(_cMaze[9],  "00001000000000000100" );
	strcpy_s(_cMaze[10], "00001000000000000100" );
	strcpy_s(_cMaze[11], "00001000000000000100" );
	strcpy_s(_cMaze[12], "00001001111111000100" );
	strcpy_s(_cMaze[13], "00001001000001000100" );
	strcpy_s(_cMaze[14], "00001001000001000100" );
	strcpy_s(_cMaze[15], "00001111000000000000" );
	strcpy_s(_cMaze[16], "00000001000000000000" );
	strcpy_s(_cMaze[17], "00000001111111111100" );
	strcpy_s(_cMaze[18], "00000000000000000100" );
	strcpy_s(_cMaze[19], "00000000000000000100" );
}

void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer)
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		--_pPlayer->tpos.y;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		++_pPlayer->tpos.y;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		--_pPlayer->tpos.x;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		++_pPlayer->tpos.x;
	Sleep(100);
}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer)
{
	system("cls");

	for (int i = 0; i < VERTICAL; ++i)
	{
		for (int j = 0; j < HORIZON; ++j)
		{
			if (i == _pPlayer->tpos.y 
				&& j == _pPlayer->tpos.x)
				cout << "§";
			else if (_cMaze[i][j] == '0') // 벽
				cout << "■";
			else if (_cMaze[i][j] == '1') // 길
				cout << " "; // 공백을 2번
			else if (_cMaze[i][j] == '2') // 시작
				cout << "▣";
			else if (_cMaze[i][j] == '3') // 도착
				cout << "♨";

		}
		cout << '\n';
	}

}
