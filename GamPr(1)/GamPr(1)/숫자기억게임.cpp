#include <iostream>
#include <Windows.h>

using namespace std;

enum Difficult {
	EASY = 1,
	NORMAL,
	HARD
};

void Init();
void GameStart(Difficult mode, int _iSleep);

void PrintNum(int mode, int *question, float *difficultSec);

int main() 
{
	Init();
	int iSelectMode = 0;
	cin >> iSelectMode;
	system("cls");
	switch (iSelectMode)
	{
	case EASY: 
	{
		GameStart(EASY, 1000);
	}
	break;
	case NORMAL:
	{
		GameStart(NORMAL, 700);
	}
	break;
	case HARD:
	{
		GameStart(HARD, 500);
	}
	break;
	default:
		break;
	}
	
}
void Init()
{
	cout << "================================\n";
	cout << "���� ��� �����Դϴ�. ��带 �����ϼ���.\n";
	cout << "EASY: 1, NORMAL: 2, HARD: 3\n";
	cout << "================================\n";
	srand((unsigned int)time(NULL));
}

void GameStart(Difficult mode, int iSleep)
{
	int repeat = mode * 5;

	int *question = new int[repeat];
	int iInput;
	for (int i = 0; i < repeat; i++) {
		question[i] = rand() % 100 + 1;
	}
	for (int i = 0; i < repeat; i++) {
		cout << question[i] << ' ';
		Sleep(iSleep);
	}
	system("cls");
	switch (mode)
	{
	case EASY:
	{
		cout << "EASY ��� �Դϴ�.\n";
	}
	break;
	case NORMAL:
	{
		cout << "NORMAL ��� �Դϴ�.\n";
	}
	break;
	case HARD:
	{
		cout << "HARD ��� �Դϴ�.\n";
	}
	break;
	default:
		break;
	}
	cout << "��� �� ���ڸ� �Է��ϼ���: \n";
	for (int i = 0; i < repeat; i++) {
		cin >> iInput;
		if (iInput != question[i]) {
			cout << "��! Ʋ�Ƚ��ϴ�.";
			delete[] question;
			return;
		}
	}
	cout << "\n�����մϴ�. ��� ���߼̳׿�.\n";
	delete[] question;
}