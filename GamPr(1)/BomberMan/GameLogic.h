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

// �ʱ�ȭ
void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, 
	PPOS _pStartpos, PPOS _pEndpos);
void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer); // �� ����
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer); // ���
