#pragma once
#include <vector>

const int HORIZON = 21;
const int VERTICAL = 20;

// 위치
typedef struct _tagpos
{
	int x;
	int y;

	bool operator==(_tagpos& pos) { return (pos.x == x && pos.y == y); }
}POS, *PPOS;

// 플레이어
typedef struct _tagplayer
{
	POS		tpos;			//플레이어 위치
	POS		tNewPos;		//플레이어 새위치
	int		iBombPow;		//폭탄 파워
	int		iBombCnt;		//폭탄 개수
	bool	bWallPush;		//벽밀기
	bool	bPushOnOff;		//벽밀기 능력 온오프
	bool	bGhost;			//슬라임능력
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
void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& vecBomb, std::vector<POS>& boomEffect); // 값 변경
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<POS>& boomEffect); // 출력
void BombCreate(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& vecBomb);
void Fire(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, POS _boompos, std::vector<POS>& boomEffect);
