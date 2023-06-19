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
	
	CARD_TYPE type;
	int value;
	std::string name;
	std::wstring image[7];
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

