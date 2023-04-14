#pragma once

const int HORIZON = 21;
const int VERTICAL = 20;

// ��ġ
typedef struct _tagpos
{
	int x;
	int y;
}POS, *PPOS;

// �÷��̾�
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


