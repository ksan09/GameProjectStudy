#include "IngameScene.h"
#include "GameLogic.h"

IngameScene::IngameScene()
{
}

IngameScene::~IngameScene()
{
}

void IngameScene::Init()
{
	srand((unsigned int)time(NULL));

	currentTurn = Turn::Draw;

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
		deckList.push_back(cardList["NormalAttack"]);
		deckList.push_back(cardList["Defense"]);
	}

	DeckShuffle(deckList);
}

void IngameScene::Update(float dt)
{
	//char inputCh = _getch();
	char inputCh;
	cin >> inputCh;

	//패뽑기
	// 나중에 지워야함 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	hand.clear();
	for (int i = 0; i < 3; ++i)
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
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	switch (currentTurn)
	{
	case Turn::Draw:
	{
		//패뽑기
		hand.clear();
		for (int i = 0; i < 3; ++i)
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
	}
		break;
	case Turn::Main:
	{

	}
		break;
	case Turn::Battle:
	{

	}
		break;
	case Turn::End:
	{

	}
		break;
	default:
		break;
	}

	
}

void IngameScene::Render()
{
	system("cls");
	cout << "1";
	// UI 렌더

	// 몬스터 렌더

	// 현재 들고 있는 패 렌더
	int x = 15;
	int y = 8;
	for (int i = 0; i < hand.size(); ++i)
	{
		CardRender(x, y, hand[i]);
		x += 10;
		y += 1;
	}

	// 현재 선택되어 있는 패 렌더

	// 현재 상황에 따라 특정한 상황 렌더
}