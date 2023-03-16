#include <iostream>
#include <Windows.h>

using namespace std;

enum Difficult {
	EASY = 1,
	NORMAL,
	HARD
};

void PrintNum(int mode, int *question, float *difficultSec);

int main() 
{
	srand((unsigned int)time(NULL));
	int question[15] = { };
	float difficultSec[3] = { 1.0f, 0.7f, 0.5f };
	int iSelectMode = 0;
	Difficult difficult = EASY;
	cout << "================================\n";
	cout << "���� ��� �����Դϴ�. ��带 �����ϼ���.\n";
	cout << "EASY: 1, NORMAL: 2, HARD: 3\n";
	cout << "================================\n";
	cin >> iSelectMode;
	switch (iSelectMode)
	{
	case EASY: 
	{
		PrintNum(iSelectMode, question, difficultSec);
	}
	break;
	case NORMAL:
	{
		PrintNum(iSelectMode, question, difficultSec);
	}
	break;
	case HARD:
	{
		PrintNum(iSelectMode, question, difficultSec);
	}
	break;
	default:
		break;
	}
	
}

void PrintNum(int mode, int *question, float *difficultSec)
{
	system("cls");
	int repeat = mode * 5;
	for (int i = 0; i < repeat; i++) {
		int randomNum = rand() % 100 + 1;
		cout << randomNum << ' ';
		question[i] = randomNum;
	}
	Sleep(difficultSec[mode - 1] * 1000);
	system("cls");
	switch (mode)
	{
	case EASY:
	{
		cout << "EASY";
	}
	break;
	case NORMAL:
	{
		cout << "NORMAL";
	}
	break;
	case HARD:
	{
		cout << "HARD";
	}
	break;
	default:
		break;
	}
	cout << " ����Դϴ�.\n";
	cout << "��� �� ���ڸ� �Է��ϼ���: \n";
	int input = 0;
	for (int i = 0; i < repeat; i++) {
		cin >> input;
		if (input != question[i]) {
			cout << "��! Ʋ�Ƚ��ϴ�.";
			return;
		}
	}
	cout << "\n�����մϴ�. ��� ���߼̳׿�.";
}