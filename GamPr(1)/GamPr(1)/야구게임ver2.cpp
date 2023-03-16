#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

bool AnswerException(int* answer);
void InputAnswer(int playerNum,int* answer);
void TurnMsg(int playerNum, int tryCount);
bool ShootProblem(int playerNum, int tryCount, int* answer);

int main()
{
	srand((unsigned int)time(NULL));

	cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n";
	cout << ":=-=-=-= 야구 게임 =-=-=-=:" << "\n";
	cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n\n";

	int p1_Answer[3] = { };
	int p2_Answer[3] = { };

	string p1_Turn = "Player1의 차례입니다.\n";
	string p2_Turn = "Player2의 차례입니다.\n";
	int turn = 0;
	int tryCount = 0;

	InputAnswer(1, p2_Answer);
	InputAnswer(2, p1_Answer);

	while (true) {
		int playerNum = turn % 2 + 1;
		if (playerNum == 1) tryCount++;
		if (ShootProblem(playerNum, tryCount, (playerNum == 1) ? p1_Answer : p2_Answer))
			return 0;
		turn++;
	}
}

bool AnswerException(int* answer) {
	for (int i = 0; i < 3; i++) {
		if ((answer[i] < 1 || 9 < answer[i])) {
			cout << "\n값은 1 ~ 9 사이의 숫자여야 합니다.\n";
			return false;
		}
	}
	if ((answer[0] == answer[1]) || (answer[1] == answer[2]) || (answer[0] == answer[2])) {
		cout << "\n값은 중복값을 넣을 수 없습니다.\n";
		return false;
	}
	return true;
}

void InputAnswer(int playerNum, int* answer)
{
	while (true) 
	{
		system("cls");
		cout << "Player" << playerNum << "의 차례입니다.\n";
		cout << "Player" << ((playerNum + 2) % 2) + 1 << "가 맞출 숫자를 입력하세요: ";

		for (int i = 0; i < 3; i++)
		{
			cin >> answer[i];
		}

		// 예외처리
		if (AnswerException(answer)) break;
		else Sleep(1000);
	}
}

void TurnMsg(int playerNum, int tryCount) {
	cout << "Player" << playerNum << "의 차례입니다.\n";
	cout << " * * * \n\n";
	cout << tryCount << "회\n";
	cout << "1 ~ 9 사이의 숫자 중 숫자 3개를 입력하세요(0 : 종료) : ";
}

bool ShootProblem(int playerNum, int tryCount, int* answer)
{
	int iStrike = 0;
	int iBall = 0;
	int inputAnswer[3] = { };

	while (true) {
		system("cls");
		TurnMsg(playerNum, tryCount);
		for (int i = 0; i < 3; i++)
		{
			cin >> inputAnswer[i];
		}
		if (AnswerException(inputAnswer)) {
			for (int i = 0; i < 3; i++) {
				if (inputAnswer[i] == answer[i])
					iStrike++;
				else if (inputAnswer[i] == answer[0] || inputAnswer[i] == answer[1] || inputAnswer[i] == answer[2])
					iBall++;
			}
			break;
		}
		else {
			Sleep(1000);
		}
	}
	

	if (iStrike == 3) {
		cout << "\n";
		cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n";
		cout << ":=-=: !Player"<< playerNum <<"  승리! :=-=: " << "\n";
		cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n\n";
		return true;
	}
	else if (iStrike == 0 && iBall == 0) {
		cout << "Out!" << "\n";
	}
	else {
		cout << iStrike << " Strike" << "\n";
		cout << iBall << " Ball" << "\n";
	}
	system("Pause");
	return false;
}