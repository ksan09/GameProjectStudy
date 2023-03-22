#include <iostream>
#include <Windows.h>

using namespace std;

void Init(int* arr, int arrSize);
void RenderNumber(int* arr, int& iBingo) {
	system("cls");

	cout << "=================================" << endl;
	cout << "|\t 빙고입니다. \t|" << endl;
	cout << "=================================" << endl;
	cout << "빙고줄이 5줄 이상이면 게임에서 승리합니다." << endl;
	cout << "=================================" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (arr[i * 5 + j] == INT_MAX)
				cout << "*" << '\t';
			else
				cout << arr[i * 5 + j] << '\t';
		}
		cout << endl;
	}

	cout << "Bingo Line: " << iBingo << endl;



}
int BingoCheck(int *arr) {
	int iBingo = 0;

	//가로 세로 체크
	for (int i = 0; i < 5; i++) {
		//가로 체크
		bool horizontalCheck = true;
		for (int j = 0; j < 5; j++) {
			if (arr[i * 5 + j] != INT_MAX) {
				horizontalCheck = false;
				break;
			}
		}

		if (horizontalCheck) iBingo++;
		//세로 체크
		bool verticalCheck = true;
		for (int j = 0; j < 5; j++) {
			if (arr[i + j*5] != INT_MAX) {
				verticalCheck = false;
				break;
			}
		}

		if (verticalCheck) iBingo++;
	}

	//대각선 체크
	//왼쪽 아래 대각선
	bool leftdownCheck = true;
	for (int i = 0; i <= 24; i+=6) {
		if (arr[i] != INT_MAX) {
			leftdownCheck = false;
			break;
		}
	}

	if (leftdownCheck) iBingo++;
	//오른쪽 아래 대각선
	bool rightdownCheck = true;
	for (int i = 4; i <= 20; i+=4) {
		if (arr[i] != INT_MAX) {
			rightdownCheck = false;
			break;
		}
	}

	if (rightdownCheck) iBingo++;

	return iBingo;

}
int Update(int* arr, int arrSize) {
	cout << "숫자를 입력하세요(0: 종료): ";
	int iInput;
	cin >> iInput;
	
	for (int i = 0; i < arrSize; ++i) {
		if (arr[i] == iInput) {
			arr[i] = INT_MAX;
			break;
		}
	}

	return iInput;
}



int main() {
	int iNumber[25] = {};
	int arrSize = (sizeof(iNumber) / sizeof(*iNumber));
	int iBingo = 0;

	Init(iNumber, arrSize);
	while (true)
	{
		iBingo = BingoCheck(iNumber);
		RenderNumber(iNumber, iBingo);
		if (iBingo >= 5) {
			cout << "게임에서 승리하셨습니다." << endl;
			break;
		}

		int input = Update(iNumber, arrSize);
		if (input == 0) {
			cout << "게임을 종료합니다." << endl;
			break;
		}
		else if (input < 1 || input > arrSize) {
			cout << "잘못 입력했습니다." << endl;
			Sleep(1000);
			continue;
		}
		

		//입력된 수를 바꿔야함.

		// 빙고 되었는지 체크하고 개수를 센다.
	}
}

void Init(int* arr, int arrSize) {

	srand((unsigned int)time(NULL));
	for (int i = 0; i < arrSize; i++) {
		arr[i] = i + 1;
	}

	for (int i = 0; i < arrSize; i++) {
		int randomIndex = rand() % (arrSize);

		int temp = arr[i];
		arr[i] = arr[randomIndex];
		arr[randomIndex] = temp;
	}
}