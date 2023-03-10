#include <iostream>

using namespace std;

int main()
{

	cout << "[========================]" << "\n";
	cout << "[=| 스타포스 강화 게임 |=]" << "\n";
	cout << "[========================]" << "\n\n";

	srand((unsigned int)time(NULL));
	int iUpgrade = 0;
	int iInput = 0;
	float fUpgradePer = rand() % 10001 / 100.f;

	cout << "현재 무기는 몇 성인가요?: ";
	cin >> iUpgrade;
	cout << "현재 무기 업그레이드: " << iUpgrade << "성\n";
	cout << "강화 확률 Percent: " << fUpgradePer << "%\n";
	cout << "강화하시겠습니까? 에: 1 아니오: 0" << "\n";
	cin >> iInput;
	if (iInput == 0)
		return 0;

	// 90퍼 50퍼 10퍼 1퍼
	if (iUpgrade <= 2) {
		if (fUpgradePer <= 90.f) {
			cout << "강화 성공!\n";
		}
		else {
			cout << "강화 실패...\n";
		}
	}
	else if (iUpgrade <= 5) {
		if (fUpgradePer <= 50.f) {
			cout << "강화 성공!\n";
		}
		else {
			cout << "강화 실패...\n";
		}
	}
	else if (iUpgrade <= 9) {
		if (fUpgradePer <= 10.f) {
			cout << "강화 성공!\n";
		}
		else {
			cout << "강화 실패...\n";
		}
	}
	else {
		if (fUpgradePer <= 1.f) {
			cout << "강화 성공!\n";
		}
		else {
			cout << "강화 실패...\n";
		}
	}

}