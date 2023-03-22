#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;



void Init(int* arr, int arrSize);
void RenderNumber(int *arr) {
	system("cls");

	cout << "=================================" << endl;
	cout << "|\t ���� ���� �����Դϴ�. \t|" << endl;
	cout << "=================================" << endl;
	cout << "*�� �������� 1���� 24���� ������� �ǵ��� ������ ���纸����." << endl;
	cout << "=================================" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (arr[i * 5 + j] == INT_MAX)
				cout << "*" << '\t';
			else
				cout << arr[i*5+j] << '\t';
		}
		cout << endl;
	}

	

}
char Update(int* arr) {
	cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ����\n";
	static int iStarIndex = 24;
	char input = _getch();

	switch (input)
	{
	case 'w':
	case 'W':
	{
		if (iStarIndex > 4) {
			arr[iStarIndex] = arr[iStarIndex - 5];
			arr[iStarIndex - 5] = INT_MAX;
			iStarIndex -= 5;
		}
	}
	break;
	case 'a':
	case 'A':
	{
		if (iStarIndex % 5 != 0) {
			arr[iStarIndex] = arr[iStarIndex - 1];
			arr[iStarIndex - 1] = INT_MAX;
			iStarIndex -= 1;
		}
	}
	break;
	case 's':
	case 'S':
	{
		if (iStarIndex < 20) {
			arr[iStarIndex] = arr[iStarIndex + 5];
			arr[iStarIndex + 5] = INT_MAX;
			iStarIndex += 5;
		}
	}
	break;
	case 'd':
	case 'D':
	{
		if (iStarIndex % 5 != 4) {
			arr[iStarIndex] = arr[iStarIndex + 1];
			arr[iStarIndex + 1] = INT_MAX;
			iStarIndex += 1;
		}
	}
	break;
	default:
		break;
	}
	return input;
}
void PuzzleClear(int* arr, int arrSize) {
	bool bChk = true;

	for(int i = 0; i < arrSize-1; ++i) {
		if (arr[i] != i + 1) {
			bChk = false;
			break;
		}
	}

	if (bChk) {
		cout << "�ٸ�����ϴ�." << endl;
		return;
	}
}

int main() {
	int iNumber[25] = {};
	int arrSize = (sizeof(iNumber) / sizeof(*iNumber));
	Init(iNumber, arrSize);
	while (true)
	{
		RenderNumber(iNumber);
		PuzzleClear(iNumber, arrSize);
		char cChk = Update(iNumber);
		if (cChk == 'q' || cChk == 'Q')
			break;
	}
}

void Init(int* arr, int arrSize) {

	srand((unsigned int)time(NULL));
	for (int i = 0; i < arrSize - 1; i++) {
		arr[i] = i + 1;
	}

	for (int i = 0; i < arrSize - 1; i++) {
		int randomIndex = rand() % (arrSize - 1);

		int temp = arr[i];
		arr[i] = arr[randomIndex];
		arr[randomIndex] = temp;
	}
	arr[arrSize-1] = INT_MAX;
}