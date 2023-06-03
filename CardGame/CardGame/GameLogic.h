#pragma once
#include "Define.h"
#include <vector>
#include <unordered_map>
using namespace std;

struct Card
{
public:
	Card();
	Card(CARD_TYPE type, int value, wstring Image[7]);
	
	CARD_TYPE type;
	int value;
	wstring image[7];
};




void Init(vector<Card>& deck, unordered_map<string, Card>& cardList);
void Update();
void Render();
void Event();

void CardRender(int posX, int posY, const Card& card);
void DeckShuffle(vector<Card>& deck);

