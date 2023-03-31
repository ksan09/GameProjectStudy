#include<iostream>
#include<Windows.h> // sleep
using namespace std;
// enum(c++98): 범위 없는. vs enum class(c++11)
// c++14, c++17, c++20 
// ::
//enum class PHONE
//{
//	IPHONE,
//	SAMSUNG,
//	LG, 
//};
enum class AI_MODE
{
	AM_EASY = 1,
	AM_NORMAL,
	AM_HARD
};
enum class LINE_NUMBER
{
	LN_H1, LN_H2, LN_H3, LN_H4, LN_H5,
	LN_V1, LN_V2, LN_V3, LN_V4, LN_V5,
	LN_LT, LN_RT
};
void Init(int* _pNumber)
{
	// 셔플
	// 값 다 들어가있어.
	for (int i = 0; i < 25; i++)
		_pNumber[i] = i + 1;
	// 섞어요.
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25; // 0 ~ 23
		idx2 = rand() % 25;
		iTemp = _pNumber[idx1];
		_pNumber[idx1] = _pNumber[idx2];
		_pNumber[idx2] = iTemp;
	}
}
// 값, 참조, 주소.
void RenderNumber(int* _pNumber, int& _iBingo)
{
	// 숫자를 출력해줄거야.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_pNumber[i * 5 + j] == INT_MAX)
				cout << "*" << "\t";
			else
				cout << _pNumber[i * 5 + j] << "\t";
		}
		cout << endl;
	}
	cout << "Bingo Line: " << _iBingo << endl;
}
void ChangeNumber(int* _pNumber, int& _iInput)
{
	// 입력된 숫자와 현재 빙고판에서 일치하는지 확인을 하고,
	// INT_MAX
	for (int i = 0; i < 25; i++)
	{
		if (_pNumber[i] == _iInput)
			_pNumber[i] = INT_MAX;
	}
}
int BingoCount(int* _pNumber)
{
	int iCntBingo = 0;
	int iHorStar = 0, iVerStar = 0, iLTStar = 0, iRTStar = 0;
	// 가로, 세로, 대각선을 체크해줄겁니다.
	for (int i = 0; i < 5; i++)
	{
		iHorStar = iVerStar = 0;
		for (int j = 0; j < 5; j++)
		{
			if (_pNumber[i * 5 + j] == INT_MAX)
				iHorStar++;
			if (_pNumber[j * 5 + i] == INT_MAX)
				iVerStar++;
		}
		if (iHorStar == 5)
			iCntBingo++;
		if (iVerStar == 5)
			iCntBingo++;
	}

	// 대각선
	for (int i = 0; i < 25; i += 6)
	{
		if (_pNumber[i] == INT_MAX)
			iLTStar++;
	}
	if (iLTStar == 5)
		iCntBingo++;
	for (int i = 4; i <= 20; i += 4)
	{
		if (_pNumber[i] == INT_MAX)
			iRTStar++;
	}
	if (iRTStar == 5)
		iCntBingo++;
	return iCntBingo;
}
AI_MODE SelectAimode()
{
	std::cout << "======================================" << endl;
	std::cout << " |\t 빙고 게임입니다.\t" << endl;
	std::cout << "======================================" << endl;
	std::cout << "빙고줄이 5줄 이상이면 게임에서 승리합니다." << endl;
	std::cout << "======================================" << endl;
	cout << "1. EASY " << endl; // 남은 것중에 랜덤
	cout << "2. NORMAL " << endl; // 현재 한 줄을 완성할 수 잇는 가능성이 가장 높은 줄 선택.
	// 3. hard: 
	// 1) 가운데 무조건 -> 양쪽 모서리 -> 대각선 -> 가장 높은줄.
	cout << "AI모드를 선택하세요: " << endl;
	int iAimode;
	cin >> iAimode;
	// C, C++, C/C++
	// 예외처리. static_cast: c++, (): c
	if (iAimode < static_cast<int>(AI_MODE::AM_EASY) ||
		iAimode >(int)AI_MODE::AM_NORMAL)
	{
		cout << "잘못 입력하셨습니다." << endl;

	}
	return (AI_MODE)iAimode;
}
int SelectAinumber(int* _pNumber, AI_MODE _eMode)
{
	// 안고른다 때문에.. 배열이 필요합니다.
	int iNoneSelect[25] = {};
	int iNoneSelectcnt = 0;
	switch (_eMode)
	{
	case AI_MODE::AM_EASY:
	{
		for (int i = 0; i < 25; i++)
		{
			if (_pNumber[i] != INT_MAX) // 숫자다.
			{
				iNoneSelect[iNoneSelectcnt] = _pNumber[i];
				++iNoneSelectcnt;
			}
		}
		return iNoneSelect[rand() % iNoneSelectcnt];
	}
	break;
	case AI_MODE::AM_NORMAL:
	{
		int iLine = 0;
		int iStarcnt = 0;
		int iSavecnt = 0;
		// 줄을 찾을 겁니다.
		// 가로 줄
		for (int i = 0; i < 5; i++)
		{
			iStarcnt = 0;
			for (int j = 0; j < 5; j++)
			{
				if (_pNumber[i * 5 + j] == INT_MAX)
					iStarcnt++;
			}
			// ???
			if (iStarcnt < 5 && iSavecnt < iStarcnt) // 빙고 줄을 바꿔주는거야. 제일 많은 줄로.
			{
				iLine = i;
				iSavecnt = iStarcnt;
			}
		}
		// 세로 줄
		for (int i = 0; i < 5; i++)
		{
			iStarcnt = 0;
			for (int j = 0; j < 5; j++)
			{
				if (_pNumber[j * 5 + i] == INT_MAX)
					iStarcnt++;
			}
			// ???
			if (iStarcnt < 5 && iSavecnt < iStarcnt) // 빙고 줄을 바꿔주는거야. 제일 많은 줄로.
			{
				iLine = i + 5;
				iSavecnt = iStarcnt;
			}
		}
		// LT 대각선
		iStarcnt = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (_pNumber[i] == INT_MAX)
				iStarcnt++;
		}
		if (iStarcnt < 5 && iSavecnt < iStarcnt) // 빙고 줄을 바꿔주는거야. 제일 많은 줄로.
		{
			iLine = (int)LINE_NUMBER::LN_LT;
			iSavecnt = iStarcnt;
		}
		// RT대각선
		iStarcnt = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (_pNumber[i] == INT_MAX)
				iStarcnt++;
		}
		if (iStarcnt < 5 && iSavecnt < iStarcnt) // 빙고 줄을 바꿔주는거야. 제일 많은 줄로.
		{
			iLine = (int)LINE_NUMBER::LN_RT;
			iSavecnt = iStarcnt;
		}
		// 줄을 알게되었따!!! 이얏호
		if (iLine <= (int)LINE_NUMBER::LN_H5) // 가로줄이다.
		{
			// 가로줄일 경우??
			for (int i = 0; i < 5; i++)
			{
				if (_pNumber[iLine * 5 + i] != INT_MAX)
					return _pNumber[iLine * 5 + i];
			}
		}
		else if (iLine <= (int)LINE_NUMBER::LN_V5) // 세로줄이다.
		{
			// 세로줄일 경우??
			for (int i = 0; i < 5; i++)
			{
				if (_pNumber[i * 5 + (iLine - 5)] != INT_MAX)
					return _pNumber[i * 5 + (iLine - 5)];
			}
		}
		else if (iLine <= (int)LINE_NUMBER::LN_LT) // LT대각선줄이다.
		{
			// LT대각선줄일 경우??
			for (int i = 0; i < 25; i += 6)
			{
				if (_pNumber[i] != INT_MAX)
					return _pNumber[i];
			}
		}
		else if (iLine <= (int)LINE_NUMBER::LN_RT) // RT대각선줄이다.
		{
			// RT대각선줄일 경우??
			for (int i = 4; i <= 20; i += 4)
			{
				if (_pNumber[i] != INT_MAX)
					return _pNumber[i];
			}
		}
		return -1;
	}
	break;
	case AI_MODE::AM_HARD:
		break;
	default:
		break;
	}
}
int main()
{
	//int a = 0;
	//float b = 0;
	//b = (float)a;
	//// 암시적 형변환. 4가지. cast 4가지.
	//// 형변환..?		// 명시적 형변환.
	//if (static_cast<int>(PHONE::IPHONE) == 0) 		
	//	cout << "아이폰입니다." << endl;

	// 1. 모드 선택
	// 2. AI 판.
	// 3. AI 선택 기준.
	srand((unsigned int)time(NULL));
	int iNumber[25] = {};
	int iAiNumber[25] = {};
	int iBingo = 0, iAiBingo = 0;
	int iInput;
	Init(iNumber);
	Init(iAiNumber);
	AI_MODE eAimode = SelectAimode();
	while (true)
	{
		system("cls");
		// Player 렌더링
		cout << "====================== Player =========================" << endl;
		RenderNumber(iNumber, iBingo);

		// ai 렌더링
		cout << "====================== AI =========================" << endl;
		switch (eAimode)
		{
		case AI_MODE::AM_EASY:
			cout << "AIMode: Easy" << endl;
			break;
		case AI_MODE::AM_NORMAL:
			cout << "AIMode: Normal" << endl;
			break;
		case AI_MODE::AM_HARD:
			cout << "AIMode: Hard" << endl;
			break;
		default:
			break;
		}
		RenderNumber(iAiNumber, iAiBingo);

		// 승리 조건 체크
		if (iBingo >= 5)
		{
			cout << "Player님이 게임에서 승리하셨습니다." << endl;
			break;
		}
		else if (iAiBingo >= 5)
		{
			cout << "AI가 게임에서 승리하셨습니다." << endl;
		}

		// 숫자 입력
		cout << "숫자를 입력하세요(0: 종료): " << endl;
		cin >> iInput;
		if (iInput == 0)
		{
			cout << "게임을 종료합니다." << endl;
			break;
		}
		else if (iInput < 1 || iInput > 25)
		{
			cout << "잘못 입력했습니다." << endl;
			continue;
		}
		// 위에서 입력받았구요.
		// 입력된 수를 별표로 바꿔야함.
		// Player 턴
		ChangeNumber(iNumber, iInput);
		ChangeNumber(iAiNumber, iInput);
		// 이제는 ai it's my turn 
		// ai모드에따라서 ai가 선택할 숫자를 만들어야 한다.
		// ??? ai 모드에 따라서 선택을 할 거시다.
		iInput = SelectAinumber(iAiNumber, eAimode);
		cout << "AI가 선택한 숫자는 " << iInput << "입니다." << endl;
		Sleep(1000);
		// AI 턴.
		ChangeNumber(iNumber, iInput);
		ChangeNumber(iAiNumber, iInput);
		// 빙고 되었는지 체크하고 개수를 센다.
		iBingo = BingoCount(iNumber);
		iAiBingo = BingoCount(iAiNumber);

	}
}