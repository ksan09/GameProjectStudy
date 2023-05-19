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
	srand((unsigned int)time(NULL));

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
		{}, 1, 0, false, false, false };
	*_pPlayer = tSetPlayer;


}

void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, 
	vector<BOOM>& vecBomb, vector<POS>& boomEffect)
{
	//========== 플레이어 움직임 ==================

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
	else if (_pPlayer->bPushOnOff &&
		_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] == '0')
	{
		_tagpos tDiffPos	= _pPlayer->tNewPos - _pPlayer->tpos;
		_tagpos testpos = tDiffPos * 2;

//		_tagpos tDoublepos	= _pPlayer->tpos + testpos;
		_tagpos tDoublepos	= _pPlayer->tpos + (tDiffPos * 2);
//		_tagpos tNextpos	= _pPlayer->tpos + tDiffPos;

		//if(_cMaze[tDoublepos.y][tDoublepos.x] == '0' && _pPlayer->bGhost)
		//	_pPlayer->tpos = _pPlayer->tNewPos;
		//else if (_cMaze[tDoublepos.y][tDoublepos.x] == '1')
		//{
		//	_cMaze[tDoublepos.y][tDoublepos.x] = '0';
		//	_cMaze[tNextpos.y][tNextpos.x] = '1';
		//	_pPlayer->tpos = _pPlayer->tNewPos;
		//}
	}
	else if (_pPlayer->bGhost)
		_pPlayer->tpos = _pPlayer->tNewPos;

	if (GetItem(_cMaze[_pPlayer->tpos.y][_pPlayer->tpos.x], _pPlayer))
	{
		_cMaze[_pPlayer->tpos.y][_pPlayer->tpos.x] = '1';
	}
	
	//========== 플레이어 움직임 ==================

	//========== 키 로직 ==================

	if (GetAsyncKeyState('E') & 0x8000)
	{
		if(_pPlayer->bWallPush)
			_pPlayer->bPushOnOff = !_pPlayer->bPushOnOff;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		BombCreate(_cMaze, _pPlayer, vecBomb);
	}
	int iBombCount = _pPlayer->iBombCnt;
	for (int i = 0; i < iBombCount; i++)
	{
		//폭탄을 가져와서 라이프를 깎고, 라이프가 0 이하면 터트림
		BOOM& boomitem = vecBomb[i];
		boomitem.life--;
		_cMaze[boomitem.y][boomitem.x] = ((boomitem.life % 10 >= 5) ? 'b' : 'p');

		if (boomitem.life <= 0)
		{
			boomitem.bDie = true;
			_pPlayer->iBombCnt--;
			Fire(_cMaze, _pPlayer, { boomitem.x, boomitem.y }, boomEffect);
		}
	}

		
	//========== 키 로직 ==================
	Sleep(100);
}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer,
	vector<POS>& boomEffect)
{
	for (int i = 0; i < VERTICAL; ++i)
	{
		for (int j = 0; j < HORIZON; ++j)
		{
			bool drawed = false;
			for (int k = 0; k < boomEffect.size(); k++)
			{
				if (boomEffect[k].y == i && boomEffect[k].x == j)
				{
					SetColor((int)COLOR::MINT, (int)COLOR::BLACK);
					cout << "▤";
					drawed = true;
					break;
				}
			}
			if (drawed) continue;
			SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);

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
			else if (_cMaze[i][j] == '4') // 물풍선 powerup
				cout << "◐";
			else if (_cMaze[i][j] == '5') // 슬라임
				cout << "♤";
			else if (_cMaze[i][j] == '6') // 벽밀기
				cout << "☜";
			else if (_cMaze[i][j] == 'b') // 물풍선!
			{
				SetColor((int)COLOR::LIGHT_BLUE, (int)COLOR::BLACK);
				cout << "⊙";
			}
			else if (_cMaze[i][j] == 'p') // 물풍선 깜빡
			{
				SetColor((int)COLOR::MINT, (int)COLOR::BLACK);
				cout << "◎";
			}
			SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
		}
		cout << '\n';
	}
	cout << "SPACEBAR: 폭탄 설치, E: 푸시능력 ON/OFF" << '\n';
	cout << "폭탄 파워: " << _pPlayer->iBombPow << '\n';
	cout << "푸시 능력: " << (_pPlayer->bPushOnOff ? "ON " : "OFF") << '\n';
	cout << "슬라임 능력: " << (_pPlayer->bGhost ? "ON " : "OFF") << '\n';
}

void BombCreate(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& vecBomb)
{
	// 폭탄 개수 5개 한정
	if (_pPlayer->iBombCnt >= 5) return;

	if (_cMaze[_pPlayer->tpos.y][_pPlayer->tpos.x] == '1')
	{
		_pPlayer->iBombCnt++;

		vecBomb.push_back({ _pPlayer->tpos.x, _pPlayer->tpos.y, 30, false });
		_cMaze[_pPlayer->tpos.y][_pPlayer->tpos.x] = 'b';
	}
}

void Fire(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, POS _boompos, std::vector<POS>& boomEffect)
{
	// 벽이 부서진다.
	_cMaze[_boompos.y][_boompos.x] = '1';

	
	// 맞으면 죽는다.
	int ibombMinRangeX = _boompos.x - _pPlayer->iBombPow;
	int ibombMaxRangeX = _boompos.x + _pPlayer->iBombPow;
	int ibombMinRangeY = _boompos.y - _pPlayer->iBombPow;
	int ibombMaxRangeY = _boompos.y + _pPlayer->iBombPow;
	if((_pPlayer->tpos.x >= ibombMinRangeX && _pPlayer->tpos.x <= ibombMaxRangeX
		&& _pPlayer->tpos.y == _boompos.y) ||
		(_pPlayer->tpos.y >= ibombMinRangeY && _pPlayer->tpos.y <= ibombMaxRangeY
		&& _pPlayer->tpos.x == _boompos.x))
		_pPlayer->tpos = { 0, 0 };
	{
		static vector<POS> vecEffect;
		for (int i = ibombMinRangeX; i <= ibombMaxRangeX; ++i)
			vecEffect.push_back({ clamp(i, 0, HORIZON - 2), _boompos.y });
		for (int i = ibombMinRangeY; i <= ibombMaxRangeY; ++i)
			vecEffect.push_back({ _boompos.x, clamp(i, 0, VERTICAL - 1) });
		
		for (const auto& pos : vecEffect)
		{
			boomEffect.push_back(pos);
			// 아이템이 나온다.
			if (_cMaze[pos.y][pos.x] == '0')
			{
				float fRandom = rand() % 10001 / 100.0f;
				if (fRandom <= 50.0f)
				{
					// 랜덤 아이템 4 ~ 6
					fRandom = rand() % 10001 / 100.0f;
					if (fRandom <= 50.0f)
						_cMaze[pos.y][pos.x] = '4'; //물풍선
					else if(fRandom <= 70.0f)
						_cMaze[pos.y][pos.x] = '5'; //슬라임
					else
						_cMaze[pos.y][pos.x] = '6'; //벽푸쉬

				}
				else
					_cMaze[pos.y][pos.x] = '1';
			}
		}
		vecEffect.clear();
	}
	
	// 이펙트 추가
	


}

void Event(std::vector<BOOM>& vecBomb, std::vector<POS>& boomEffect)
{
	vector<BOOM>::iterator iter = vecBomb.begin();
	for (; iter!=vecBomb.end();)
	{
		if (iter->bDie)
			iter = vecBomb.erase(iter);
		else
			iter++;
	}

	vector<POS>::iterator iterEffect = boomEffect.begin();
	for (; iterEffect != boomEffect.end();)
	{
		iter = vecBomb.erase(iter);
	}
}

bool GetItem(char _cItem, PPLAYER _pPlayer)
{
	if (_cItem == '4')
	{
		++_pPlayer->iBombPow;
		return true;
	}
	else if (_cItem == '5')
	{
		_pPlayer->bGhost = true;
		return true;
	}
	else if (_cItem == '6')
	{
		_pPlayer->bWallPush = true;
		_pPlayer->bPushOnOff = true;
		return true;
	}

	return false;
}
