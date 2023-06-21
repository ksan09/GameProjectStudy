#include "pch.h"
#include "ExplainScene.h"
#include "SceneManager.h"
#include "console.h"

ExplainScene::ExplainScene()
{
	state = ExplainState::Menu;
	startIdx = 0;
	maxIdx = 0;
}

ExplainScene::~ExplainScene()
{
}

void ExplainScene::Init()
{
	state = ExplainState::Menu;
	startIdx = 0;
	maxIdx = 3;
}

void ExplainScene::Update(float dt)
{
	char inputCh = ' ';
	switch (state)
	{
	case ExplainState::Menu:
	{
		inputCh = _getch();
		switch (inputCh)
		{
		case 'w':
		case 'W':
			if (startIdx == 0) return;
			startIdx--;
			break;
		case 's':
		case 'S':
			if (startIdx == maxIdx) return;
			startIdx++;
			break;
		case ' ':
			switch (startIdx)
			{
			case 0:
				state = ExplainState::AttackCard;
				break;
			case 1:
				state = ExplainState::DefenseCard;
				break;
			case 2:
				state = ExplainState::GameRule;
				break;
			case 3:
				GET_SINGLE(SceneManager)->LoadScene(L"IntroScene");
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
		break;
	case ExplainState::AttackCard:
		inputCh = _getch();
		if (inputCh == ' ')
			state = ExplainState::Menu;
		break;
	case ExplainState::DefenseCard:
		inputCh = _getch();
		if (inputCh == ' ')
			state = ExplainState::Menu;
		break;
	case ExplainState::GameRule:
		inputCh = _getch();
		if (inputCh == ' ')
			state = ExplainState::Menu;
		break;
	default:
		break;
	}
}

void ExplainScene::Render()
{
	wstring menu[3] = {
			L"      ╔╦╗╔═╗╔╗╔╦ ╦          ",
			L"      ║║║║╣ ║║║║ ║          ",
			L"      ╩ ╩╚═╝╝╚╝╚═╝          ",
	};

	switch (state)
	{
	case ExplainState::Menu:
	{
		system("cls");
		GoToxy(5, 3);
		cout << "어떠한 부분에 대한 설명이 필요하신가요?";
		
		wstring attackCard[3] = {
			L"      ╔═╗╔╦╗╔╦╗╔═╗╔═╗╦╔═  ╔═╗╔═╗╦═╗╔╦╗        ",
			L"      ╠═╣ ║  ║ ╠═╣║  ╠╩╗  ║  ╠═╣╠╦╝ ║║        ",
			L"      ╩ ╩ ╩  ╩ ╩ ╩╚═╝╩ ╩  ╚═╝╩ ╩╩╚══╩╝        ",
		};
		SelectUIRender((startIdx == 0), 8, attackCard);
		wstring defenseCard[3] = {
			L"      ╔╦╗╔═╗╔═╗╔═╗╔╗╔╔═╗╔═╗  ╔═╗╔═╗╦═╗╔╦╗         ",
			L"       ║║║╣ ╠╣ ║╣ ║║║╚═╗║╣   ║  ╠═╣╠╦╝ ║║         ",
			L"      ═╩╝╚═╝╚  ╚═╝╝╚╝╚═╝╚═╝  ╚═╝╩ ╩╩╚══╩╝         ",
		};
		SelectUIRender((startIdx == 1), 13, defenseCard);
		wstring gamerule[3] = {
			L"      ╔═╗╔═╗╔╦╗╔═╗  ╦═╗╦ ╦╦  ╔═╗         ",
			L"      ║ ╦╠═╣║║║║╣   ╠╦╝║ ║║  ║╣          ",
			L"      ╚═╝╩ ╩╩ ╩╚═╝  ╩╚═╚═╝╩═╝╚═╝         ",
		};
		SelectUIRender((startIdx == 2), 18, gamerule);
		wstring back[3] = {
			L"      ╔╗ ╔═╗╔═╗╦╔═          ",
			L"      ╠╩╗╠═╣║  ╠╩╗          ",
			L"      ╚═╝╩ ╩╚═╝╩ ╩╝          ",
		};
		SelectUIRender((startIdx == 3), 23, back);
	}
		break;
	case ExplainState::AttackCard:
		system("cls");
		GoToxy(5, 3);
		cout << "공격 카드에 대해서 설명해드리겠습니다." << '\n';
		cout << '\n';
		cout << "- 플레이어의 공격 카드" << '\n';
		cout << '\n';
		cout << " 적에게 이름 밑에 적혀있는 숫자만큼의 데미지를 줍니다." << '\n';
		cout << '\n';
		cout << "- 몬스터의 공격 카드" << '\n';
		cout << '\n';
		cout << " 플레이어에게 1의 데미지를 줍니다." << '\n';
		SelectUIRender(true, 23, menu);
		break;
	case ExplainState::DefenseCard:
		system("cls");
		GoToxy(5, 3);
		cout << "방어 카드에 대해서 설명해드리겠습니다." << '\n';
		cout << '\n';
		cout << "- 플레이어의 방어 카드" << '\n';
		cout << '\n';
		cout << " 이름 밑에 적혀있는 숫자만큼" << '\n';
		cout << " 방어 카드가 놓여져 있는 칸에서" << '\n';
		cout << " 뒤에 있는 칸에 적의 공격 카드가 있을 경우" << '\n';
		cout << " 적의 공격 카드를 제거합니다." << '\n';
		cout << '\n';
		cout << "- 몬스터의 방어 카드" << '\n';
		cout << '\n';
		cout << " 방어 카드가 놓여져 있는 칸에서" << '\n';
		cout << " 1칸 뒤에 플레이어의 공격 카드가 있을 경우" << '\n';
		cout << " 플레이어의 공격 카드를 제거합니다." << '\n';
		SelectUIRender(true, 23, menu);
		break;
	case ExplainState::GameRule:
		system("cls");
		GoToxy(5, 3);
		cout << "게임 룰에 대해서 설명해드리겠습니다." << '\n';
		cout << '\n';
		cout << " 게임을 시작하면 카드를 4장 뽑습니다." << '\n';
		cout << '\n';
		cout << " 5개의 칸에서 몬스터가 n개의 칸을 먼저 차지합니다." << '\n';
		cout << '\n';
		cout << " 플레이어가 Space를 눌러서 현재 선택하고 있는 카드를 " << '\n';
		cout << " 남은 칸에서 제일 앞에 있는 부분에다가 집어 넣습니다." << '\n';
		cout << '\n';
		cout << " E를 눌러서 턴을 넘기게 되면" << '\n';
		cout << " 맨 처음 칸부터 마지막 칸까지 안에 있는 카드가 실행됩니다." << '\n';
		SelectUIRender(true, 23, menu);

		break;
	default:
		break;
	}
}

void ExplainScene::SelectUIRender(bool select, int posY, wstring str[3])
{
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	GoToxy(0, posY);
	if (select == true) SetColor((int)COLOR::LIGHT_YELLOW, (int)COLOR::BLACK);
	for (int i = 0; i < 3; ++i)
	{
		if (select && i == 1)
		{
			GoToxy(0, posY + i);
			wcout << L"  >";
		}
		else if (select) GoToxy(3, posY + i);
		wcout << str[i] << '\n';
	}
	if (select == true) SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
	iCurmode = _setmode(_fileno(stdout), _O_TEXT);
}
