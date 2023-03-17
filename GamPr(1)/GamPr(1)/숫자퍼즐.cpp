#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void Init(int* arr, int arrSize);

void RenderNumber(int *arr) {
	system("cls");

	cout << "===================================" << endl;
	cout << "|\t 숫자 퍼즐 게임입니다. \t|" << endl;
	cout << "===================================" << endl;
	cout << "*을 움직여서 1부터 24까지 순서대로 되도록 퍼즐을 맞춰보세요." << endl;
	cout << "===================================" << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (arr[i * 5 + j] == INT_MAX)
				cout << "*" << '\t';
			else
				cout << arr[i*5+j] << '\t';
		}
		cout << endl;
	}

	cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료\n";

}

void Update(int* arr) {

}

int main() {
	int iNumber[25] = {};
	Init(iNumber, (sizeof(iNumber) / sizeof(*iNumber)));
	while (true)
	{
		RenderNumber(iNumber);
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
}