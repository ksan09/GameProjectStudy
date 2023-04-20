#pragma once

const int HORIZON = 21;
const int VERTICAL = 20;

// 위치
typedef struct _tagpos
{
	int x;
	int y;
}POS, *PPOS;

// 플레이어
typedef struct _tagplayer
{
	POS tpos;
	int iBombPow;
	int iBombCnt;
	bool bWallPush;
	bool bPushOnOff;
	bool bGhost;
}PLAYER, *PPLAYER;

typedef struct _tagboom
{
	int x;
	int y;
	int life;
	bool bDie;
}BOOM, * PBOOM;

// 초기화
void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, 
	PPOS _pStartpos, PPOS _pEndpos);
void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer); // 값 변경
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer); // 출력
