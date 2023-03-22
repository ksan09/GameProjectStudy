#include <iostream>
#include <Windows.h>

using namespace std;

void Init(int* arr, int arrSize);
void RenderNumber(int* arr, int& iBingo) {
	system("cls");

	cout << "=================================" << endl;
	cout << "|\t �����Դϴ�. \t|" << endl;
	cout << "=================================" << endl;
	cout << "�������� 5�� �̻��̸� ���ӿ��� �¸��մϴ�." << endl;
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

	//���� ���� üũ
	for (int i = 0; i < 5; i++) {
		//���� üũ
		bool horizontalCheck = true;
		for (int j = 0; j < 5; j++) {
			if (arr[i * 5 + j] != INT_MAX) {
				horizontalCheck = false;
				break;
			}
		}

		if (horizontalCheck) iBingo++;
		//���� üũ
		bool verticalCheck = true;
		for (int j = 0; j < 5; j++) {
			if (arr[i + j*5] != INT_MAX) {
				verticalCheck = false;
				break;
			}
		}

		if (verticalCheck) iBingo++;
	}

	//�밢�� üũ
	//���� �Ʒ� �밢��
	bool leftdownCheck = true;
	for (int i = 0; i <= 24; i+=6) {
		if (arr[i] != INT_MAX) {
			leftdownCheck = false;
			break;
		}
	}

	if (leftdownCheck) iBingo++;
	//������ �Ʒ� �밢��
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
	cout << "���ڸ� �Է��ϼ���(0: ����): ";
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
			cout << "���ӿ��� �¸��ϼ̽��ϴ�." << endl;
			break;
		}

		int input = Update(iNumber, arrSize);
		if (input == 0) {
			cout << "������ �����մϴ�." << endl;
			break;
		}
		else if (input < 1 || input > arrSize) {
			cout << "�߸� �Է��߽��ϴ�." << endl;
			Sleep(1000);
			continue;
		}
		

		//�Էµ� ���� �ٲ����.

		// ���� �Ǿ����� üũ�ϰ� ������ ����.
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