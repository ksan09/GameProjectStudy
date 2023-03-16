#include <iostream>
#include <vector>

using namespace std;

int main() 
{
	srand((unsigned int)time(NULL));

	cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n";
	cout << ":=-=-=-= �߱� ���� =-=-=-=:" << "\n";
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
		cout << iGamecount << "��° �õ�" << "\n";
		cout << "1 ~ 9 ������ ���� �� ���� 3���� �Է��ϼ���(0 ����): ";

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
				cout << "�߸��� ���ڸ� �Է��߽��ϴ�." << "\n";
				cout << "ó������ �ٽ� �Է����ּ���." << "\n";
				i = 0;
				iStrike = 0;
				iBall = 0;
			}
		}

		cout << "\n";

		if (iStrike == 3) {
			
			cout << ":=-=-=-=-=-=-=-=-=-=-=-=-=:" << "\n";
			cout << ":=-=: !!���� Ŭ����!! :=-=:" << "\n";
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
