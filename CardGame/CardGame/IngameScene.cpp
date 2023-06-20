#include <algorithm>
#include "pch.h"
#include "console.h"
#include "IngameScene.h"
#include "GameLogic.h"

IngameScene::IngameScene()
{
	currentSelectCardIndex = 0;
	currentTurn = Turn::Draw;
	maxCardIndex = 4;
}

IngameScene::~IngameScene()
{
}

void IngameScene::Init()
{
	srand((unsigned int)time(NULL));

	currentTurn = Turn::Draw;
	currentSelectCardIndex = 0;
	maxCardIndex = 4;

	wstring tempEmptyImage[7] =
	{
		L"                ",
		L"                ",
		L"                ",
		L"                ",
		L"                ",
		L"                ",
		L"                ",
	};
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
	wstring tempPowerAtkImage[7] =
	{
		L"                ",
		L"       █        ",
		L"  █    ██  █    ",
		L"     █ ████  █  ",
		L"   █  ████      ",
		L"       ██       ",
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
	tempCard = { CARD_TYPE::ATK, 18, "PowerAttack", tempPowerAtkImage };
	cardList["PowerAtk"] = tempCard;
	tempCard = { CARD_TYPE::DEF, 1, "Sheild", tempSheildImage };
	cardList["Defense"] = tempCard;
	tempCard = { CARD_TYPE::EMPTY, 0, "Empty", tempEmptyImage };
	cardList["Empty"] = tempCard;

	tempCard = { CARD_TYPE::EnemyATK, 1, "EnemyAttack", tempAttackImage };
	cardList["EnemyAttack"] = tempCard;
	tempCard = { CARD_TYPE::EnemyDEF, 1, "EnemyAttack", tempSheildImage };
	cardList["EnemyDefense"] = tempCard;

	// 기본 덱 생성
	for (int i = 0; i < 3; ++i)
	{
		deckList.push_back(cardList["NormalAttack"]);
		deckList.push_back(cardList["Defense"]);
	}
	deckList.push_back(cardList["PowerAtk"]);

	for (int i = 0; i < 5; ++i)
		block[i] = cardList["Empty"];

	DeckShuffle(deckList);
}

void IngameScene::Update(float dt)
{
	//패뽑기
	switch (currentTurn)
	{
	case Turn::Draw:
	{
		for (int i = 0; i < 5; ++i)
			block[i] = cardList["Empty"];

		int enemySelectArr[] = { 0, 1, 2, 3, 4 };
		for (int i = 0; i < 5; ++i)
		{
			int randIdx = rand() % (5 - i) + i;

			int temp = enemySelectArr[randIdx];
			enemySelectArr[randIdx] = enemySelectArr[i];
			enemySelectArr[i] = temp;
		}
		block[enemySelectArr[0]] = cardList["EnemyDefense"];
		block[enemySelectArr[1]] = cardList["EnemyAttack"];

		sort(enemySelectArr + 2, enemySelectArr + 5);
		for (int i = 2; i < 5; ++i)
			blockQ.push(enemySelectArr[i]);

		//패뽑기
		hand.clear();
		for (int i = 0; i < maxCardIndex; ++i)
		{
			// 덱이 비었다면 다시 섞는다.
			if (deck.empty())
			{
				DeckShuffle(deckList);
				for (auto card : deckList)
					deck.push(card);
			}

			hand.push_back(deck.front());
			deck.pop();
		}

		currentTurn = Turn::Main;
	}
		break;
	case Turn::Main:
	{
		char inputCh = _getch();

		switch (inputCh)
		{
		case 'a':
		case 'A':
		{
			// 왼쪽
			currentSelectCardIndex--;
			if (currentSelectCardIndex < 0)
				currentSelectCardIndex = 0;
		}
		break;
		case 'd':
		case 'D':
		{
			// 오른쪽
			currentSelectCardIndex++;
			if (currentSelectCardIndex > maxCardIndex-1)
				currentSelectCardIndex = maxCardIndex-1;

		}
		break;
		case ' ':
		{
			// 선택
			if (hand[currentSelectCardIndex].type == CARD_TYPE::EMPTY)
				return;

			if (blockQ.empty())
				return;

			int idx = blockQ.front();
			blockQ.pop();

			block[idx] = hand[currentSelectCardIndex];
			hand.erase(hand.begin() + currentSelectCardIndex);
			currentSelectCardIndex = 0;

		}
		break;
		case 'e':
		case 'E':
		{
			// 엔드 페이즈
			currentTurn = Turn::Battle;
		}
		break;
		default:
			break;
		}
	}
		break;
	case Turn::Battle:
	{
		currentTurn = Turn::End;
	}
		break;
	case Turn::End:
	{
		currentTurn = Turn::Draw;
	}
		break;
	default:
		break;
	}

	
}

void IngameScene::Render()
{
	system("cls");

	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);

	// 테두리 렌더
	SetColor((int)COLOR::LIGHT_YELLOW, (int)COLOR::BLACK);
	GoToxy(0, 0);
	wcout << L"██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██";
	for (int i = 2; i < 27; i+=2)
	{
		
		GoToxy(0, i);
		wcout << L"██                                                          ██";
	}
	GoToxy(0, 28);
	wcout << L"██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██";
	SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);

	// 몬스터 렌더
	

	// 카드 게임 UI 렌더

	// 카드를 놨두는 장소
	for (int i = 0; i < 5; ++i)
	{
		CARD_TYPE cardType = block[i].type;
		COLOR cardColor = COLOR::WHITE;

		if (cardType == CARD_TYPE::ATK)
			cardColor = COLOR::VIOLET;
		else if (cardType == CARD_TYPE::DEF)
			cardColor = COLOR::LIGHT_BLUE;
		else if (cardType == CARD_TYPE::EnemyATK)
			cardColor = COLOR::RED;
		else if (cardType == CARD_TYPE::EnemyDEF)
			cardColor = COLOR::BLUE;

		SetColor((int)cardColor, (int)COLOR::BLACK);
		int px = 5 + i * 12;
		int py = 4;
		GoToxy(px, py++);
		wcout << L"████";
		GoToxy(px, py);
		wcout << L"████";
	}
	SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);

	// 현재 들고 있는 패 렌더
	int x = 3;
	int y = 11;
	for (int i = 0; i < hand.size(); ++i)
	{
		if (i == currentSelectCardIndex)
		{
			x += 12;
			y += 1;
			continue;
		}

		CardRender(x, y, hand[i]);
		x += 12;
		y += 1;
	}

	x = 3 + 12 * currentSelectCardIndex;
	y = 11 + currentSelectCardIndex - 1;
	CardRender(x, y, hand[currentSelectCardIndex]);

	// 현재 선택되어 있는 패 렌더

	// 현재 상황에 따라 특정한 상황 렌더

	iCurmode = _setmode(_fileno(stdout), O_TEXT);
}