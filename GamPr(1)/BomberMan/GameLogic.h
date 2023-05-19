#pragma once
#include <vector>

const int HORIZON = 21;
const int VERTICAL = 20;

// ��ġ
typedef struct _tagpos
{
	int x;
	int y;

	_tagpos operator*(int v) { return { x* v, y* v }; }
	_tagpos operator+(_tagpos& pos) { return { x + pos.x, y + pos.y }; }
	_tagpos operator-(_tagpos& pos) { return { x - pos.x, y - pos.y }; }
	bool operator==(_tagpos& pos) { return (pos.x == x && pos.y == y); }
}POS, *PPOS;
//_tagpos

// �÷��̾�
typedef struct _tagplayer
{
	_tagpos		tpos;			//�÷��̾� ��ġ
	POS		tNewPos;		//�÷��̾� ����ġ
	int		iBombPow;		//��ź �Ŀ�
	int		iBombCnt;		//��ź ����
	bool	bWallPush;		//���б�
	bool	bPushOnOff;		//���б� �ɷ� �¿���
	bool	bGhost;			//�����Ӵɷ�
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
void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& vecBomb, std::vector<POS>& boomEffect); // �� ����
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<POS>& boomEffect); // ���
void BombCreate(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& vecBomb);
void Fire(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, POS _boompos, std::vector<POS>& boomEffect);
void Event(std::vector<BOOM>& vecBomb, std::vector<POS>& boomEffect);
bool GetItem(char _cItem, PPLAYER _pPlayer);
