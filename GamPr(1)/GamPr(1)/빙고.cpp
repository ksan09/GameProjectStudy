#include <iostream>
#include <Windows.h>

using namespace std;

enum class Difficult {
	EASY = 1,
	NORMAL,
	HARD,
	HELL,
};

void Init(int* arr, int* aiArr, int arrSize);
Difficult SelectAimode() {
	cout << "===============================================" << endl;
	cout << "      |\t ���� ���� ���� �Դϴ�. \t|" << endl;
	cout << "===============================================" << endl;
	cout << "�������� 5�� �̻��̸� ���ӿ��� �¸��մϴ�." << endl;
	cout << "===============================================" << endl;
	cout << "1. Easy\n";
	cout << "2. Normal\n";
	cout << "3. Hard\n";
	cout << "4. Hell\n";
	cout << "ai��带 �����ϼ���: ";

	int difficult;
	cin >> difficult;

	if (difficult < (int)Difficult::EASY || difficult > (int)Difficult::HELL) {
		cout << "�߸� �Է��ϼ̽��ϴ�." << '\n';
		//SelectAimode();
	}

	return (Difficult)difficult;
}
void RenderNumber(int* arr, int& iBingo) {
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
int SelectAiNumber(int *arr, int arrSize, Difficult difficult) {

	int iNoneSelect[25] = {};
	int iNoneSelectCnt = 0;

	switch (difficult)
	{
	case Difficult::EASY:
	{
		for (int i = 0; i < 25; ++i) {
			if (arr[i] != INT_MAX) {
				iNoneSelect[iNoneSelectCnt] = arr[i];
				++iNoneSelectCnt;
			}
		}

		int randSelectIndex = rand() % iNoneSelectCnt;
		return iNoneSelect[randSelectIndex];
	}
		break;
	case Difficult::NORMAL:
	{

	}
		break;
	case Difficult::HARD:
	{

	}
		break;
	case Difficult::HELL:
	{

	}
		break;
	default:
		break;
	}
	return 0;
}
int BingoCheck(int* arr) {
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
			if (arr[i + j * 5] != INT_MAX) {
				verticalCheck = false;
				break;
			}
		}

		if (verticalCheck) iBingo++;
	}

	//�밢�� üũ
	//���� �Ʒ� �밢��
	bool leftdownCheck = true;
	for (int i = 0; i <= 24; i += 6) {
		if (arr[i] != INT_MAX) {
			leftdownCheck = false;
			break;
		}
	}

	if (leftdownCheck) iBingo++;
	//������ �Ʒ� �밢��
	bool rightdownCheck = true;
	for (int i = 4; i <= 20; i += 4) {
		if (arr[i] != INT_MAX) {
			rightdownCheck = false;
			break;
		}
	}

	if (rightdownCheck) iBingo++;

	return iBingo;

}
void ChangeNum(int* arr, int num, int arrSize) {
	
	for (int i = 0; i < arrSize; ++i) {
		if (arr[i] == num) {
			arr[i] = INT_MAX;
		}

	}

}
void AIInput(int* arr, int* aiArr, int arrSize, Difficult difficult) {
	int aiChooseNum = 0;

	//AI�� ���ڸ� �����Ѵ�.
	switch (difficult)
	{
	case Difficult::EASY:
		break;
	case Difficult::NORMAL:
		break;
	case Difficult::HARD:
		break;
	case Difficult::HELL:
		break;
	default:
		break;
	}


	int cnt = 0;
	for (int i = 0; i < arrSize; ++i) {
		if (arr[i] == aiChooseNum) {
			arr[i] = INT_MAX;
			cnt++;
		}
		if (aiArr[i] == aiChooseNum) {
			aiArr[i] = INT_MAX;
			cnt++;
		}
		if (cnt == 2) break;
	}
}


int main() {
	srand((unsigned int)time(NULL));

	int iNumbers[25] = {};
	int iAINumbers[25] = {};
	int arrSize = (sizeof(iNumbers) / sizeof(*iNumbers));
	int iBingo = 0;
	int iAIBingo = 0;

	Init(iNumbers, iAINumbers, arrSize);
	Difficult iDifficult = SelectAimode();

	while (true)
	{
		system("cls");
		//�÷��̾� ������
		cout << "================= Player =================" << endl;
		RenderNumber(iNumbers, iBingo);
		//AI ������
		cout << "=================== AI ===================" << endl;
		
		switch (iDifficult)
		{
		case Difficult::EASY:
			cout << "AIMode: Easy" << '\n';
			break;
		case Difficult::NORMAL:
			cout << "AIMode: Normal" << '\n';
			break;
		case Difficult::HARD:
			cout << "AIMode: Hard" << '\n';
			break;
		case Difficult::HELL:
			cout << "AIMode: Hell" << '\n';
			break;
		default:
			break;
		}

		RenderNumber(iAINumbers, iAIBingo);

		// �¸� ���� üũ
		if (iBingo >= 5 && iAIBingo >= 5) {
			cout << "���º�" << endl;
			break;
		}
		else if (iBingo >= 5) {
			cout << "Player �¸�" << endl;
			break;
		}
		else if (iAIBingo >= 5) {
			cout << "AI �¸�" << endl;
			break;
		}

		// ���� �Է�
		cout << "���ڸ� �Է��ϼ���(0: ����): ";
		int input;
		cin >> input;

		// ���� ó��
		if (input == 0) {
			cout << "������ �����մϴ�." << endl;
			break;
		}
		else if (input < 1 || input > arrSize) {
			cout << "�߸� �Է��߽��ϴ�." << endl;
			Sleep(1000);
			continue;
		}

		// �Էµ� ���� ��ǥ�� �ٲ����
		ChangeNum(iNumbers, input, arrSize);
		ChangeNum(iAINumbers, input, arrSize);

		// ai��忡 ���� ai�� ������ ���ڸ� ������ �Ѵ�. 
		input = SelectAiNumber(iAINumbers, arrSize, iDifficult);
		
		// �Էµ� ���� ��ǥ�� �ٲ����
		ChangeNum(iNumbers, input, arrSize);
		ChangeNum(iAINumbers, input, arrSize);

		
		iBingo = BingoCheck(iNumbers);
		iAIBingo = BingoCheck(iAINumbers);
		
		
	}
}

void Init(int* arr, int* aiArr, int arrSize) {

	for (int i = 0; i < arrSize; i++) {
		arr[i] = i + 1;
		aiArr[i] = i + 1;
	}

	for (int i = 0; i < arrSize; i++) {
		int randomIndex = rand() % (arrSize - i) + i;

		int temp = arr[i];
		arr[i] = arr[randomIndex];
		arr[randomIndex] = temp;
	}

	for (int i = 0; i < arrSize; i++) {
		int randomIndex = rand() % (arrSize - i) + i;

		int temp = aiArr[i];
		aiArr[i] = aiArr[randomIndex];
		aiArr[randomIndex] = temp;
	}
}