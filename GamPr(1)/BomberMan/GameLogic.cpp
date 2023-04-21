#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include <vector>
#include "GameLogic.h"
#include "console.h"
#pragma comment(lib, "winmm.lib")

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

	_pStartpos->x = 0;
	_pStartpos->y = 0;
	_pEndpos->x = 19;
	_pEndpos->y = 8;

	PLAYER tSetPlayer = { *_pStartpos, 
		1, 0, false, false, false };
	*_pPlayer = tSetPlayer;


}

void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, 
	vector<BOOM> vecBomb, vector<POS> boomEffect)
{
	_pPlayer->tNewPos = _pPlayer->tpos;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		--_pPlayer->tNewPos.y;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		++_pPlayer->tNewPos.y;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		--_pPlayer->tNewPos.x;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		++_pPlayer->tNewPos.x;

	_pPlayer->tNewPos.x = std::clamp(_pPlayer->tNewPos.x, 0, HORIZON -2);
	_pPlayer->tNewPos.y = std::clamp(_pPlayer->tNewPos.y, 0, VERTICAL-1);

	if (_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] != '0')
		_pPlayer->tpos = _pPlayer->tNewPos;

	if (_kbhit())
	{
		int iInput = _getch();
		if (iInput == 32)
		{
			BOOM boom = { _pPlayer->tpos.x,
			_pPlayer->tpos.y, 10, false };

			vecBomb.push_back(boom);

			_cMaze[_pPlayer->tpos.y][_pPlayer->tpos.x] = 'b';
		}
	}
	
		
	Sleep(100);
}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer,
	vector<POS> boomEffect)
{
	for (int i = 0; i < VERTICAL; ++i)
	{
		for (int j = 0; j < HORIZON; ++j)
		{
			if (i == _pPlayer->tpos.y
				&& j == _pPlayer->tpos.x)
				cout << "¡×";
			else if (_cMaze[i][j] == '0') // º®
				cout << "¡á";
			else if (_cMaze[i][j] == '1') // ±æ
				cout << " "; // °ø¹éÀ» 2¹ø
			else if (_cMaze[i][j] == '2') // ½ÃÀÛ
				cout << "¢Ã";
			else if (_cMaze[i][j] == '3') // µµÂø
				cout << "¢Í";
			else if (_cMaze[i][j] == '4') // ¹°Ç³¼± powerup
				cout << "¢Ä";
			else if (_cMaze[i][j] == '4') // ½½¶óÀÓ
				cout << "¢»";
			else if (_cMaze[i][j] == '4') // º®¹Ð±â
				cout << "¢Ð";
			else if (_cMaze[i][j] == 'b') // ¹°Ç³¼±!
			{
				SetColor((int)COLOR::LIGHT_BLUE, (int)COLOR::BLACK);
				cout << "¢Á";
			}
			else if (_cMaze[i][j] == 'p') // ¹°Ç³¼± ±ôºý
			{
				SetColor((int)COLOR::MINT, (int)COLOR::BLACK);
				cout << "¡Ý";
			}
			SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
		}
		cout << '\n';
	}

}
