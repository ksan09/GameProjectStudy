#include <iostream>

using namespace std;

int main()
{

	cout << "[========================]" << "\n";
	cout << "[=| ��Ÿ���� ��ȭ ���� |=]" << "\n";
	cout << "[========================]" << "\n\n";

	srand((unsigned int)time(NULL));
	int iUpgrade = 0;
	int iInput = 0;
	float fUpgradePer = rand() % 10001 / 100.f;

	cout << "���� ����� �� ���ΰ���?: ";
	cin >> iUpgrade;
	cout << "���� ���� ���׷��̵�: " << iUpgrade << "��\n";
	cout << "��ȭ Ȯ�� Percent: " << fUpgradePer << "%\n";
	cout << "��ȭ�Ͻðڽ��ϱ�? ��: 1 �ƴϿ�: 0" << "\n";
	cin >> iInput;
	if (iInput == 0)
		return 0;

	// 90�� 50�� 10�� 1��
	if (iUpgrade <= 2) {
		if (fUpgradePer <= 90.f) {
			cout << "��ȭ ����!\n";
		}
		else {
			cout << "��ȭ ����...\n";
		}
	}
	else if (iUpgrade <= 5) {
		if (fUpgradePer <= 50.f) {
			cout << "��ȭ ����!\n";
		}
		else {
			cout << "��ȭ ����...\n";
		}
	}
	else if (iUpgrade <= 9) {
		if (fUpgradePer <= 10.f) {
			cout << "��ȭ ����!\n";
		}
		else {
			cout << "��ȭ ����...\n";
		}
	}
	else {
		if (fUpgradePer <= 1.f) {
			cout << "��ȭ ����!\n";
		}
		else {
			cout << "��ȭ ����...\n";
		}
	}

}