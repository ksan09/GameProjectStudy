#pragma once
#include "Define.h"
#include <vector>
#include <queue>
#include <unordered_map>
//using namespace std;

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




void Init(std::vector<Card>& deck, std::unordered_map<std::string, Card>& cardList);
void Update(std::vector<Card>& deck, std::queue<Card>& playDeck, std::vector<Card>& hand);
void Render(std::vector<Card>& hand);
void Event();

void CardRender(int posX, int posY, const Card& card);
void DeckShuffle(std::vector<Card>& deck);

