#include "pch.h"
#include "GameLogic.h"
#include "console.h"
#include "SceneManager.h"

using namespace std;



void CardRender(int posX, int posY, const Card& card)
{
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);

	int cardColor = 0;
	if (card.type == CARD_TYPE::ATK)
		cardColor = (int)COLOR::VIOLET;
	else if (card.type == CARD_TYPE::DEF)
		cardColor = (int)COLOR::LIGHT_BLUE;

	GoToxy(posX, posY);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	wcout << L"█";
	SetColor(cardColor, (int)COLOR::WHITE);
	wcout << L"██████████████████" << '\n';
	GoToxy(posX, posY + 1);
	// 나중에 카드 이미지도 출력해야함

	for (int i = 0; i < 7; ++i)
	{
		SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
		wcout << L"█";
		SetColor(cardColor, (int)COLOR::WHITE);
		wcout << L"█" << card.image[i] << L"█" << '\n';
		GoToxy(posX, posY + 2 + i);
	}
	
	GoToxy(posX, posY + 8);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	wcout << L"█";
	SetColor(cardColor, (int)COLOR::WHITE);
	wcout << L"██████████████████" << '\n';
	GoToxy(posX, posY + 9);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	wcout << L"█";
	SetColor(cardColor, (int)COLOR::WHITE);
	wcout << L"██████████████████" << '\n';

	GoToxy(posX, posY + 10);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	wcout << L"█";
	SetColor(cardColor, (int)COLOR::WHITE);
	wcout << L"█";
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	iCurmode = _setmode(_fileno(stdout), O_TEXT);
	cout << " " << card.name;
	iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i < 15 - card.name.length(); ++i)
		wcout << L" ";
	SetColor(cardColor, (int)COLOR::WHITE);
	wcout <<L"█" << '\n';
	GoToxy(posX, posY + 11);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	wcout << L"█";
	SetColor(cardColor, (int)COLOR::WHITE);
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
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	wcout << L"█";
	SetColor(cardColor, (int)COLOR::WHITE);
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

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::Init()
{
	//GET_SINGLE(SceneManager)->Init();
}

void GameLogic::Update()
{
	UINT64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	m_deltaTime = (currentCount - m_prevCount) / static_cast<float>(m_frequency);
	m_prevCount = currentCount;

	GET_SINGLE(SceneManager)->Update(m_deltaTime);
}

void GameLogic::Render()
{
	GET_SINGLE(SceneManager)->Render();
}
