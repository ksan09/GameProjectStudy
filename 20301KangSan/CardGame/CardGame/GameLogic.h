#pragma once
#include "Define.h"
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Card
{
public:
	Card();
	Card(CARD_TYPE type, int value, std::string name, std::wstring Image[7]);
	~Card();
	
	CARD_TYPE type;
	int value;
	std::string name;
	std::wstring image[7];
};
class Monster 
{
public:
	Monster();
	Monster(string name, int hp, std::vector<CARD_TYPE> mobPattern, std::wstring image[15]);
	~Monster();

public:
	void OnDamage(int damage);

public:
	bool GetDie()		{ return isDie;		}
	string GetName()	{ return name;		}
	int GetHp()			{ return hp;		}
	int GetMaxHp()		{ return maxHp;		}
	int GetCardCnt()	{ return cardCnt;	}
	std::wstring image[15];
	std::vector<CARD_TYPE> mobPattern;

private:
	bool isDie;
	string name;
	int hp;
	int maxHp;
	int cardCnt;
};

class GameLogic
{
public:
	GameLogic();
	~GameLogic();

public:
	void Init();
	void Update();
	void Render();

private:
	UINT64	m_frequency = 0;
	UINT64	m_prevCount = 0;
	float	m_deltaTime = 0.0f;

private:
	UINT	m_frameCount = 0;
	float	m_frameTime = 0.0f;
};

void CardRender(int posX, int posY, const Card& card);
void MobRender(int posX, int posY, Monster& mob, int color);
void DeckShuffle(std::vector<Card>& deck);

