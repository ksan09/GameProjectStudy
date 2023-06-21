#include <algorithm>
#include "pch.h"
#include "console.h"
#include "IngameScene.h"
#include "GameLogic.h"
#include "SceneManager.h"

using namespace std;

IngameScene::IngameScene()
{
	currentSelectCardIndex = 0;
	p_state = PlayerState::None;
	currentTurn = Turn::Draw;
	maxCardIndex = 4;
	battleBlock = 0;
	playerHP = 10;
	playerMaxHP = 10;
	battleTime = 0;
	systemText = "";
}

IngameScene::~IngameScene()
{
}

void IngameScene::Init()
{
	srand((unsigned int)time(NULL));

	p_state = PlayerState::None;
	currentTurn = Turn::Draw;
	currentSelectCardIndex = 0;
	maxCardIndex = 4;
	battleBlock = 0;
	playerHP = 10;
	playerMaxHP = 10;
	battleTime = 0;
	systemText = "";

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

	// 몬스터 리스트 생성
	wstring tempMobImage[15] =
	{
		L"                          ",
		L"          ∧＿∧            ",
		L"         (・ω・)           ",
		L"     ┏ーー∪ー∪ーー┓    ",
		L"     ┃＼　　　　　／┃    ",
		L"     ┃　＼　♡　／　┃    ",
		L"     ┃　／＼＿／＼　┃    ",
		L"     ┗ー━ー ━ ー━ ー┛    ",
		L"                          ",
		L"                          ",
		L"                          ",
		L"                          ",
		L"                          ",
		L"                          ",
		L"                          ",
	};
	wstring tempMobImage2[15] =
	{
		L"",
		L" .､ゞヾ∧\"\"'∧;,       ",
		L" ヾ　　　・ω・ 彡    Z z z",
		L" ﾐ　　　　o　 o　 ミ     ",
		L"~彡　　　　　　　 ﾐ      ",
		L" / ｿ,,　,０; ,;; :､０ヾ` ",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
	};
	wstring tempMobImage3[15] =
	{
		L"",
		L"(V)∧_∧(V)           ",
		L" ヽ(･ω･)ﾉ   꽃게다요 ",
		L"  /  /                ",
		L" ノ￣ゝ               ",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",

	};
	wstring tempMobImage4[15] =
	{
		L"",
		L"∧__∧",
		L"(｀Д´ ) ",
		L"(っ▄︻▇〓┳═☆",
		L"/     )",
		L"(/ ￣∪",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
		L"",
	};
	RegisterMob("*AK-Cat*", 40, 4, tempMobImage4);
	RegisterMob("LetterCat", 80, 3, tempMobImage);
	RegisterMob("BigCat", 240, 1, tempMobImage2);
	RegisterMob("CrapCat", 120, 2, tempMobImage3);
	int randomMobIdx = rand() % mobNameList.size();
	currentMonster = mobList[mobNameList[randomMobIdx]];
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
		for (int i = 0; i < currentMonster.GetCardCnt(); ++i)
		{
			bool attackCard = rand() % 2;
			block[enemySelectArr[i]] = (attackCard ? cardList["EnemyAttack"] : cardList["EnemyDefense"]);
		}
		sort(enemySelectArr + currentMonster.GetCardCnt(), enemySelectArr + 5);
		while(!blockQ.empty())
			blockQ.pop();
		for (int i = currentMonster.GetCardCnt(); i < 5; ++i)
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

		systemText = "카드를 선택하세요!";
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
			if (blockQ.empty())
				return;
			if (hand.empty())
				return;
			if (hand[currentSelectCardIndex].type == CARD_TYPE::EMPTY)
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
			battleBlock = 0;
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
		Sleep(800);
		systemText = "";
		if (battleBlock >= 5)
		{
			systemText = "새롭게 패를 뽑는 중입니다.";
			currentTurn = Turn::End;
			break;
		}

		Card& tempCard = block[battleBlock];
		switch (tempCard.type)
		{
		case CARD_TYPE::ATK:
		{
			p_state = PlayerState::ATK;
			systemText = "DAMAGE! -" + to_string(tempCard.value);
			currentMonster.OnDamage(tempCard.value);
		}
		break;
		case CARD_TYPE::DEF:
		{
			p_state = PlayerState::DEF;
			if ((battleBlock + 1) < 5 && block[battleBlock + 1].type == CARD_TYPE::EnemyATK)
			{
				systemText = "DEFENSED!";
				block[battleBlock + 1] = cardList["Empty"];
			}
		}
		break;
		case CARD_TYPE::EnemyATK:
		{
			systemText = "ATTACK!";
			p_state = PlayerState::Damaged;
			playerHP--;
		}
		break;
		case CARD_TYPE::EnemyDEF:
		{
			p_state = PlayerState::MonsterDEF;
			if (battleBlock + 1 >= 5) break;
			if (block[battleBlock + 1].type == CARD_TYPE::ATK)
			{
				block[battleBlock + 1] = cardList["Empty"];
				systemText = "DEFENSE!";
			}
			else
			{
				systemText = "FAIL DEFENSE..";
			}
		}
		break;
		default:
			p_state = PlayerState::None;
			break;
		}
		tempCard = cardList["Empty"];
		battleBlock++;
		currentTurn = Turn::Animation;

		if (playerHP <= 0)
			systemText = "Player Dead!";
		else if (currentMonster.GetDie() == true)
			systemText = "Monster Dead!";
	}
	break;
	case Turn::Animation:
	{
		Sleep(200);
		p_state = PlayerState::None;

		currentTurn = Turn::Battle;
	}
	break;
	case Turn::End:
	{
		if (playerHP <= 0)
			GET_SINGLE(SceneManager)->LoadScene(L"IntroScene");
		if (currentMonster.GetDie() == true)
			GET_SINGLE(SceneManager)->LoadScene(L"IntroScene");

		p_state = PlayerState::None;
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
	int color = (int)COLOR::LIGHT_YELLOW;
	if (p_state == PlayerState::Damaged)
		color = (int)COLOR::LIGHT_RED;
	else if (p_state == PlayerState::DEF)
		color = (int)COLOR::LIGHT_BLUE;

	SetColor(color, (int)COLOR::BLACK);
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
	int mobColor = (int)COLOR::WHITE;
	if (p_state == PlayerState::ATK)
		mobColor = (int)COLOR::RED;
	else if (p_state == PlayerState::MonsterDEF)
		mobColor = (int)COLOR::BLUE;
	MobRender(70, 5, currentMonster, mobColor);
	
	// systemText렌더
	// 현재 상황에 따라 특정한 상황 렌더
	GoToxy(70, 20);
	cout << systemText;

	// 카드 게임 UI 렌더
	GoToxy(70, 22);
	cout << "A, D \t- 선택된 카드 이동 ";
	GoToxy(70, 23);
	cout << "space \t- 카드 선택 ";
	GoToxy(70, 24);
	cout << "E \t- 턴 넘기기";

	iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);

	// 플레이어 체력 UI 렌더
	GoToxy(70, 25);
	SetColor((int)COLOR::LIGHT_RED, (int)COLOR::GRAY);
	float hpPer = playerHP / (float)playerMaxHP * 30.0f + 1;
	for (int i = 0; i < 30; ++i)
		wcout << (i <= hpPer ? L"█" : L" ");
	iCurmode = _setmode(_fileno(stdout), _O_TEXT);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	cout << " " << playerHP << "/ " << playerMaxHP << " ";
	iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);

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
	if (!hand.empty())
	{
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

		// 현재 선택되어 있는 패 렌더
		x = 3 + 12 * currentSelectCardIndex;
		y = 11 + currentSelectCardIndex - 1;
		CardRender(x, y, hand[currentSelectCardIndex]);
	}

	iCurmode = _setmode(_fileno(stdout), O_TEXT);
	GoToxy(2, 27);
}

void IngameScene::RegisterMob(string name, int hp, int cardCnt, wstring mobImage[15])
{
	Monster tempMob = { name, hp, cardCnt, mobImage };
	mobNameList.push_back(name);
	mobList[name] = tempMob;
}
