﻿#include "pch.h"
#include "GameLogic.h"
#include "console.h"
#include "SceneManager.h"

using namespace std;

void CardRender(int posX, int posY, const Card& card)
{
	if (card.type == CARD_TYPE::EMPTY)
		return;

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

void MobRender(int posX, int posY, Monster& mob, int color)
{
	int hpPer = 30 * mob.GetHp() / (float)mob.GetMaxHp() + 1;

	int iCurmode = _setmode(_fileno(stdout), O_TEXT);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	GoToxy(posX, posY++);
	cout << mob.GetName();
	iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	SetColor((int)COLOR::RED, (int)COLOR::GRAY);
	GoToxy(posX, posY);
	for (int i = 0; i < 30; ++i)
		wcout << (i < hpPer ? L"█" : L" ");
	iCurmode = _setmode(_fileno(stdout), O_TEXT);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	cout << " " << mob.GetHp() << "/ " << mob.GetMaxHp() << " ";
	iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	posY += 2;
	SetColor(color, (int)COLOR::BLACK);
	for (int i = 0; i < 15; ++i)
	{
		GoToxy(posX, posY + i);
		wcout << mob.image[i];
	}
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
Card::~Card()
{
}

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
	GET_SINGLE(SceneManager)->Release();
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

Monster::Monster()
{
	name = "";
	isDie = false;
	mobPattern.clear();
	cardCnt = 0;
	maxHp = 5;
	hp = 5;
	for (int i = 0; i < 15; ++i)
		image[i] = L" ";
}
Monster::Monster(string name, int hp, std::vector<CARD_TYPE> mobPattern, std::wstring image[15]) : name{ name }, cardCnt{ (int)mobPattern.size()}, hp{hp}, maxHp{hp}
{
	for (int i = 0; i < mobPattern.size(); ++i)
		this->mobPattern.push_back(mobPattern[i]);
	isDie = false;
	for (int i = 0; i < 15; ++i)
		this->image[i] = image[i];
}
Monster::~Monster()
{
}
void Monster::OnDamage(int damage)
{
	hp -= damage;
	if (hp <= 0)
		isDie = true;
}
