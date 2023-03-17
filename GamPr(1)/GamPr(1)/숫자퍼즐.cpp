#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void Init(int* arr, int arrSize);

void RenderNumber(int *arr) {
	system("cls");

	cout << "===================================" << endl;
	cout << "|\t ���� ���� �����Դϴ�. \t|" << endl;
	cout << "===================================" << endl;
	cout << "*�� �������� 1���� 24���� ������� �ǵ��� ������ ���纸����." << endl;
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

	cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ����\n";

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