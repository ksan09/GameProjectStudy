#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <string>
#include "GameLogic.h"
#include "console.h"

using namespace std;

void Init(vector<Card>& deck, unordered_map<string, Card> cardList)
{
	srand((unsigned int)time(NULL));

	wstring tempAttackImage[7] =
	{
		L"                ",
		L"        █████   ",
		L"      █████     ",
		L"     ████       ",
		L"    ███         ",
		L"   ██           ",
		L"                ",
	};
	wstring tempSheildImage[7] =
	{
		L"                ",
		L"   ██████████   ",
		L"   ██      ██   ",
		L"   ██      ██   ",
		L"    ██    ██    ",
		L"     ██████     ",
		L"                ",
	};
	Card tempCard = { CARD_TYPE::ATK, 14, "Attack", tempAttackImage };
	cardList["NormalAttack"] = tempCard;
	tempCard = { CARD_TYPE::DEF, 1, "Sheild", tempSheildImage };
	cardList["Defense"] = tempCard;
	
	// 기본 덱 생성
	for (int i = 0; i < 3; ++i)
	{
		deck.push_back(cardList["NormalAttack"]);
		deck.push_back(cardList["Defense"]);
	}

	DeckShuffle(deck);
}

void Update(vector<Card>& deck, queue<Card>& playDeck, vector<Card>& hand)
{
	char inputCh;
	cin >> inputCh;

	//패뽑기
	hand.clear();
	for (int i = 0; i < 3; ++i)
	{
		// 덱이 비었다면 다시 섞는다.
		if (playDeck.empty())
		{
			DeckShuffle(deck);
			for (auto card : deck)
				playDeck.push(card);
		}

		hand.push_back(playDeck.front());
		playDeck.pop();
	}
}

void Render(vector<Card>& hand)
{
	system("cls");

	int x = 2;
	int y = 20;
	for (int i = 0; i < hand.size(); ++i)
	{
		CardRender(x, y, hand[i]);
		x += 4;
		y += 2;
	}
	
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

	for (int i = 0; i < 7; ++i)
	{
		wcout << L"█" << card.image[i] << L"█" << '\n';
		GoToxy(posX, posY + 2 + i);
	}
	
	GoToxy(posX, posY + 8);
	wcout << L"██████████████████" << '\n';
	GoToxy(posX, posY + 9);
	wcout << L"██████████████████" << '\n';

	GoToxy(posX, posY + 10);
	wcout << L"█";
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	iCurmode = _setmode(_fileno(stdout), O_TEXT);
	cout << " " << card.name;
	iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i < 15 - card.name.length(); ++i)
		wcout << L" ";
	if (card.type == CARD_TYPE::ATK)
		SetColor((int)COLOR::LIGHT_VIOLET, (int)COLOR::WHITE);
	else if (card.type == CARD_TYPE::DEF)
		SetColor((int)COLOR::LIGHT_BLUE, (int)COLOR::WHITE);
	wcout <<L"█" << '\n';
	GoToxy(posX, posY + 11);
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

Card::Card(CARD_TYPE type, int value, string name, wstring image[7])
	: type{type}, value{value}, name{name}
{
	for (int i = 0; i < 7; ++i)
		this->image[i] = image[i];
}
