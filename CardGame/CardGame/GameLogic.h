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
	Monster(int hp, std::wstring image[15]);
	~Monster();

public:
	void OnDamage(int damage);

public:
	bool GetDie()	{ return isDie; }
	int GetHp()		{ return hp;	}
	int GetMaxHp()	{ return maxHp; }
	std::wstring image[15];

private:
	bool isDie;
	int hp;
	int maxHp;
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
void DeckShuffle(std::vector<Card>& deck);

