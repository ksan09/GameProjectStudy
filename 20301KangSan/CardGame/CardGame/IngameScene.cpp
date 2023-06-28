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
	CursorSet(false, NULL);

	p_state = PlayerState::None;
	currentTurn = Turn::Draw;
	currentSelectCardIndex = 0;
	maxCardIndex = 4;
	battleBlock = 0;
	playerHP = 10;
	playerMaxHP = 10;
	battleTime = 0;
	systemText = "";
	hand.clear();
	cardNameList.clear();
	cardList.clear();
	deckList.clear();
	mobNameList.clear();
	mobList.clear();
	while (!deck.empty())
		deck.pop();
	while (!blockQ.empty())
		blockQ.pop();

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
	wstring tempSuperAtkImage[7] =
	{
		L"                ",
		L"         ████   ",
		L"   █  █████     ",
		L"  ██ ████       ",
		L"  █████████     ",
		L"  ████          ",
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
	wstring tempSuperNovaImage[7] =
	{
		L"                ",
		L"       ██       ",
		L"   ██      ██   ",
		L"       ██       ",
		L"   ██      ██   ",
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
	wstring tempLongSheildImage[7] =
	{
		L"                ",
		L"  ████████████  ",
		L"  ██        ██  ",
		L"  ██        ██  ",
		L"   ██      ██   ",
		L"    ████████    ",
		L"                ",
	};

	Card tempCard = { CARD_TYPE::ATK, 12, "Attack", tempAttackImage };
	cardList["NormalAttack"] = tempCard;
	cardList["PowerAtk"] = tempCard;
	tempCard = { CARD_TYPE::DEF, 1, "Sheild", tempSheildImage };
	cardList["Defense"] = tempCard;
	tempCard = { CARD_TYPE::EMPTY, 0, "Empty", tempEmptyImage };
	cardList["Empty"] = tempCard;
	RegisterCard(CARD_TYPE::ATK, 18, "PowerAttack", tempPowerAtkImage);
	RegisterCard(CARD_TYPE::ATK, 20, "SuperAttack", tempSuperAtkImage);
	RegisterCard(CARD_TYPE::ATK, 25, "SuperNova", tempSuperNovaImage);
	RegisterCard(CARD_TYPE::DEF, 2, "LongSheild", tempLongSheildImage);

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
	deckList.push_back(cardList["PowerAttack"]);

	for (int i = 0; i < 5; ++i)
		block[i] = cardList["Empty"];
	for (int i = 0; i < 2; ++i)
		clearCard[i] = cardList["Empty"];

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
	vector<CARD_TYPE> tempMobPattern1 = { CARD_TYPE::EnemyATK, CARD_TYPE::EnemyDEF, CARD_TYPE::EnemyATK };
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
	vector<CARD_TYPE> tempMobPattern2 = { CARD_TYPE::EnemyATK, CARD_TYPE::EnemyDEF, CARD_TYPE::EnemyDEF };
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
	vector<CARD_TYPE> tempMobPattern3 = { CARD_TYPE::EnemyATK, CARD_TYPE::EnemyATK };
	wstring tempMobImage4[15] =
	{
		L"",
		L"∧__∧",
		L"(｀Д´ )       두다다다다닷",
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
	vector<CARD_TYPE> tempMobPattern4 = { CARD_TYPE::EnemyATK, CARD_TYPE::EnemyATK, CARD_TYPE::EnemyATK };
	wstring tempMobImage5[15] =
	{
		L"",
		L".　 ∧＿＿∧ ＿∧                 ",
		L"(（(・ω・)三ω・)) 때려봐 때려봐~",
		L"  (っっ = っっ゜　휘익 휘익       ",
		L"   ヽ　　ノ                       ", 
		L"   (/ ￣∪                        ",    
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
	vector<CARD_TYPE> tempMobPattern5 = { CARD_TYPE::EnemyDEF, CARD_TYPE::EnemyDEF, CARD_TYPE::EnemyDEF };
	wstring tempMobImage6[15] =
	{
		L"",
		L"∧＿∧",
		L"(　･ω･)＝つ≡つ",
		L"(っ　≡つ＝つ",
		L"./　　　) 바바바바",
		L"( /￣∪",
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
	vector<CARD_TYPE> tempMobPattern6 = { CARD_TYPE::EnemyATK, CARD_TYPE::EnemyATK, CARD_TYPE::EnemyDEF };
	

	RegisterMob("LetterCat", 60, tempMobPattern1, tempMobImage);
	RegisterMob("BigCat", 140, tempMobPattern2, tempMobImage2);
	RegisterMob("CrapCat", 80, tempMobPattern3, tempMobImage3);
	RegisterMob("*AK-Cat*", 30, tempMobPattern4, tempMobImage4);
	RegisterMob("AvoidCat", 40, tempMobPattern5, tempMobImage5);
	RegisterMob("BoxingCat", 100, tempMobPattern6, tempMobImage6);
	
	currentMonster = NextRandomMob();
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

		//몬스터 칸 차지 로직
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
			Card mobCard = cardList["Empty"];
			if (currentMonster.mobPattern[i] == CARD_TYPE::EnemyATK)
				mobCard = cardList["EnemyAttack"];
			else if (currentMonster.mobPattern[i] == CARD_TYPE::EnemyDEF)
				mobCard = cardList["EnemyDefense"];

			block[enemySelectArr[i]] = mobCard;
		}
		std::sort(enemySelectArr + currentMonster.GetCardCnt(), enemySelectArr + 5);
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
			//PlaySound(TEXT("Game/Sound/Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
			currentSelectCardIndex--;
			if (currentSelectCardIndex < 0)
				currentSelectCardIndex = 0;
			PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
		}
		break;
		case 'd':
		case 'D':
		{
			// 오른쪽
			//PlaySound(TEXT("Game/Sound/Select"), nullptr, SND_FILENAME | SND_ASYNC);
			currentSelectCardIndex++;
			if (currentSelectCardIndex > hand.size() - 1)
				currentSelectCardIndex = (int)hand.size() - 1;
			PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
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

			PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
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
			return;
		}

		Card tempCard = block[battleBlock];
		while (tempCard.type == CARD_TYPE::EMPTY)
		{
			battleBlock++;
			if (battleBlock >= 5)
				return;
			tempCard = block[battleBlock];
		}
			
		
		switch (tempCard.type)
		{
		case CARD_TYPE::ATK:
		{
			PlaySound(TEXT("Damaged.wav"), nullptr, SND_FILENAME | SND_ASYNC);
			p_state = PlayerState::ATK;
			systemText = "DAMAGE! -" + to_string(tempCard.value);
			currentMonster.OnDamage(tempCard.value);
		}
		break;
		case CARD_TYPE::DEF:
		{
			p_state = PlayerState::DEF;
			if ((battleBlock + tempCard.value) < 5 && block[battleBlock + tempCard.value].type == CARD_TYPE::EnemyATK)
			{
				PlaySound(TEXT("Block.wav"), nullptr, SND_FILENAME | SND_ASYNC);
				systemText = "DEFENSED!";
				block[battleBlock + tempCard.value] = cardList["Empty"];
			}
			else
			{
				systemText = "FAIL DEFENSED..";
				PlaySound(TEXT("FalseBlock.wav"), nullptr, SND_FILENAME | SND_ASYNC);
			}
		}
		break;
		case CARD_TYPE::EnemyATK:
		{
			PlaySound(TEXT("Hit.wav"), nullptr, SND_FILENAME | SND_ASYNC);
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
				PlaySound(TEXT("Block.wav"), nullptr, SND_FILENAME | SND_ASYNC);
				block[battleBlock + 1] = cardList["Empty"];
				systemText = "DEFENSE!";
			}
			else
			{
				PlaySound(TEXT("FalseBlock.wav"), nullptr, SND_FILENAME | SND_ASYNC);
				systemText = "FAIL DEFENSE..";
			}
		}
		break;
		default:
			p_state = PlayerState::None;
			break;
		}
		block[battleBlock] = cardList["Empty"];
		battleBlock++;
		currentTurn = Turn::Animation;

		if (playerHP <= 0)
		{
			systemText = "Player Dead!";
			currentTurn = Turn::End;
		}
		else if (currentMonster.GetDie() == true)
		{
			systemText = "Monster Dead!";
			currentTurn = Turn::End;
		}
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
		else if (currentMonster.GetDie() == true)
		{
			PlaySound(TEXT("ChangeScreen.wav"), nullptr, SND_FILENAME | SND_ASYNC);
			for (int i = 0; i < 2; ++i)
				clearCard[i] = RandomCard();
			currentTurn = Turn::Clear;
		}
		else
			currentTurn = Turn::Draw;

		p_state = PlayerState::None;
	}
		break;
	case Turn::Clear:
	{
		if (mobNameList.empty() == true)
		{
			//클리어 사운드 추가
			PlaySound(TEXT("GameClear.wav"), nullptr, SND_FILENAME | SND_ASYNC);
			GET_SINGLE(SceneManager)->LoadScene(L"GameClearScene");
			return;
		}
		PlaySound(TEXT("DeathMob.wav"), nullptr, SND_FILENAME | SND_ASYNC);
		currentMonster = NextRandomMob();

		playerHP += 3;
		if (playerHP > playerMaxHP)
			playerHP = playerMaxHP;

		while (true)
		{
			char inputCh = _getch();
			if (inputCh == '1')
			{
				PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
				deckList.push_back(clearCard[0]);
				break;
			}
			else if (inputCh == '2')
			{
				PlaySound(TEXT("Select.wav"), nullptr, SND_FILENAME | SND_ASYNC);
				deckList.push_back(clearCard[1]);
				break;
			}
		}
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

	if (currentTurn == Turn::Clear)
	{
		//게임 보상 창 렌더
		GoToxy(0, 3);
		std::cout << "          !적 처치!        " << '\n';
		std::cout << '\n';
		std::cout << "        HP를 3회복합니다  " << '\n';
		std::cout << "   추가 카드 보상을 선택하세요  " << '\n';
		std::cout << '\n';

		CardRender(2, 8, clearCard[0]);
		CardRender(30, 8, clearCard[1]);
		GoToxy(3, 25);
		std::cout << "1, 2중 하나를 입력하여서 몇번째 카드를 획득하실지 정할 수 있습니다." << '\n';
		
		return;
	}
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);

	// 테두리 렌더
	int color = (int)COLOR::LIGHT_YELLOW;
	if (p_state == PlayerState::Damaged)
		color = (int)COLOR::LIGHT_RED;
	else if (p_state == PlayerState::DEF)
		color = (int)COLOR::LIGHT_BLUE;

	SetColor(color, (int)COLOR::BLACK);
	GoToxy(0, 0);
	std::wcout << L"██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██";
	for (int i = 2; i < 27; i+=2)
	{
		GoToxy(0, i);
		std::wcout << L"██                                                          ██";
	}
	GoToxy(0, 28);
	std::wcout << L"██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██";
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
	std::cout << systemText;

	// 카드 게임 UI 렌더
	GoToxy(70, 22);
	std::cout << "A, D \t- 선택된 카드 이동 ";
	GoToxy(70, 23);
	std::cout << "space \t- 카드 선택 ";
	GoToxy(70, 24);
	std::cout << "E \t- 턴 넘기기";

	iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);

	// 플레이어 체력 UI 렌더
	GoToxy(70, 25);
	SetColor((int)COLOR::LIGHT_RED, (int)COLOR::GRAY);
	float hpPer = playerHP / (float)playerMaxHP * 30.0f + 1;
	for (int i = 0; i < 30; ++i)
		std::wcout << (i <= hpPer ? L"█" : L" ");
	iCurmode = _setmode(_fileno(stdout), _O_TEXT);
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	std::cout << " " << playerHP << "/ " << playerMaxHP << " ";
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
		std::wcout << L"████";
		GoToxy(px, py);
		std::wcout << L"████";
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

void IngameScene::RegisterMob(string name, int hp, vector<CARD_TYPE> mobPattern, wstring mobImage[15])
{
	Monster tempMob = { name, hp, mobPattern, mobImage };
	mobNameList.push_back(name);
	mobList[name] = tempMob;
}

void IngameScene::RegisterCard(CARD_TYPE type, int value, string name, wstring cardImage[7])
{
	Card tempCard = { type, value, name, cardImage };
	cardList[name] = tempCard;
	cardNameList.push_back(name);
}

Monster IngameScene::NextRandomMob()
{
	int randomMobIdx = rand() % mobNameList.size();
	Monster tempMob = mobList[mobNameList[randomMobIdx]];

	// 소환한 몹 다시 안 나오게 지우기?
	mobNameList.erase(mobNameList.begin() + randomMobIdx);

	return tempMob;
}

Card IngameScene::RandomCard()
{
	if (mobNameList.empty() == true)
	{
		return Card();
	}

	int randomMobIdx = rand() % cardNameList.size();
	Card tempCard = cardList[cardNameList[randomMobIdx]];

	return tempCard;
}
