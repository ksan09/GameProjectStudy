#include "GameLogic.h"
#include "console.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>

using namespace std;

void Init(vector<Card>& deck, unordered_map<string, Card> cardList)
{
	srand((unsigned int)time(NULL));

	//cardList["NormalAttack"] = { CARD_TYPE::ATK, 8 };
	//cardList["Defense"] = { CARD_TYPE::DEF, 5 };
	
	// 기본 덱 생성
	for (int i = 0; i < 3; ++i)
	{
		deck.push_back(cardList["NormalAttack"]);
		deck.push_back(cardList["Defense"]);
	}

	DeckShuffle(deck);
}

void Update()
{
}

void Render()
{
}

void Event()
{
}

void CardRender(int posX, int posY, const Card& card)
{
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);

	if(card.type == CARD_TYPE::ATK)
		SetColor((int)COLOR::LIGHT_VIOLET, (int)COLOR::WHITE);
	else if (card.type == CARD_TYPE::DEF)
		SetColor((int)COLOR::LIGHT_BLUE, (int)COLOR::WHITE);
	GoToxy(posX, posY);
	wcout << L"██████████████████" << '\n';
	GoToxy(posX, posY + 1);
	// 나중에 카드 이미지도 출력해야함

	wcout << L"█░░░░░░░░░░░░░░░░█" << '\n';
	GoToxy(posX, posY + 2);
	wcout << L"█░░░░░░░░░░░░░░░░█" << '\n';
	GoToxy(posX, posY + 3);
	wcout << L"█░░░░░░░░░░░░░░░░█" << '\n';
	GoToxy(posX, posY + 4);
	wcout << L"█░░░░░░░░░░░░░░░░█" << '\n';
	GoToxy(posX, posY + 5);
	wcout << L"█░░░░░░░░░░░░░░░░█" << '\n';
	GoToxy(posX, posY + 6);
	wcout << L"█░░░░░░░░░░░░░░░░█" << '\n';
	GoToxy(posX, posY + 7);
	wcout << L"█░░░░░░░░░░░░░░░░█" << '\n';
	GoToxy(posX, posY + 8);
	wcout << L"██████████████████" << '\n';
	GoToxy(posX, posY + 9);
	wcout << L"██████████████████" << '\n';

	GoToxy(posX, posY + 10);
	wcout << L"█";
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	if (card.type == CARD_TYPE::ATK)
	{
		wcout << L" ATK ";
		wcout << to_wstring(card.value);
		wcout << "         ";
	}
	else if (card.type == CARD_TYPE::DEF)
	{
		wcout << L" DEF [";
		wcout << to_wstring(card.value);
		wcout << "]        ";
	}
	else
	{
		wcout << L" Null          ";
	}
	if (card.type == CARD_TYPE::ATK)
		SetColor((int)COLOR::LIGHT_VIOLET, (int)COLOR::WHITE);
	else if (card.type == CARD_TYPE::DEF)
		SetColor((int)COLOR::LIGHT_BLUE, (int)COLOR::WHITE);

	wcout << L"█" << '\n';

	GoToxy(posX, posY + 11);
	wcout << L"█";
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	wcout << L"                ";
	if (card.type == CARD_TYPE::ATK)
		SetColor((int)COLOR::LIGHT_VIOLET, (int)COLOR::WHITE);
	else if (card.type == CARD_TYPE::DEF)
		SetColor((int)COLOR::LIGHT_BLUE, (int)COLOR::WHITE);
	wcout <<L"█" << '\n';
	GoToxy(posX, posY + 12);
	wcout << L"██████████████████" << '\n';

	SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
	iCurmode = _setmode(_fileno(stdout), O_TEXT);
}

void DeckShuffle(vector<Card>& deck)
{
	// 덱 셔플
	for (int i = 0; i < deck.size(); ++i)
	{
		int randomindex = rand() % (deck.size() - i) + i;
		Card temp = deck[i];
		deck[i] = deck[randomindex];
		deck[randomindex] = temp;
	}
}

Card::Card()
{
	type = CARD_TYPE::ATK; 
	value = 0;
	for (int i = 0; i < 7; ++i)
	{
		image[i] = L"                ";
	}
	
}

Card::Card(CARD_TYPE type, int value, wstring Image[7])
{
}
