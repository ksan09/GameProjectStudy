#include <iostream>
#include <vector>

using namespace std;

int main() 
{
	srand((unsigned int)time(NULL));

	cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n";
	cout << ":=-=-=-= 야구 게임 =-=-=-=:" << "\n";
	cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n\n";

	vector<int> vec;
	int nums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (int i = 0; i < 9; i++) {
		int randomIndex = rand() % (9 - i) + i;

		int temp = nums[i];
		nums[i] = nums[randomIndex];
		nums[randomIndex] = temp;
	}
	
	for (int i = 0; i < 3; i++) {
		vec.push_back(nums[i]);
	}

	int iGamecount = 0;

	while (true) {
		iGamecount++;
		cout << iGamecount << "번째 시도" << "\n";
		cout << "1 ~ 9 사이의 숫자 중 숫자 3개를 입력하세요(0 종료): ";

		int iStrike = 0;
		int iBall = 0;

		for (int i = 0; i < 3; i++) 
		{
			int iInput = 0;
			cin >> iInput;
			if(iInput == 0) {
				return 0;
			}
			else if (vec[i] == iInput) {
				iStrike++;
			}
			else if (find(vec.begin(), vec.end(), iInput) != vec.end()) {
				iBall++;
			}
			else {
				cout << "잘못된 숫자를 입력했습니다." << "\n";
				cout << "처음부터 다시 입력해주세요." << "\n";
				i = 0;
				iStrike = 0;
				iBall = 0;
			}
		}

		cout << "\n";

		if (iStrike == 3) {
			
			cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n";
			cout << ":=-=: !!게임 클리어!! :=-=:" << "\n";
			cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n\n";
			return 0;
		}
		else if (iStrike == 0 && iBall == 0) {
			cout << "Out!" << "\n";
		}
		else {
			cout << iStrike << " Strike" << "\n";
			cout << iBall << " Ball" << "\n";
		}
		cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n\n";
	}
}
