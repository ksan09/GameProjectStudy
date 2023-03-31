#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

int main() {
	srand((unsigned int)time(NULL));
	bool isEnd = false;

	while (!isEnd)
	{
		int randSoundIdx = rand() % 8;
		string soundName[8] = { "도", "레", "미", "파", "솔", "라", "시", "도" };
		double sounds[8] = { 523.25, 587.33, 659.26, 698.46, 783.99, 880, 987.77, 1046.5 };

		system("cls");

		cout << "------------------" << '\n';
		cout << "| 절대 음감 게임 |" << '\n';
		cout << "------------------" << '\n';
		cout << "설명 : 처음에 8음계를 들려 주고," << '\n';
		cout << " 다음에 8개 중 한 개의 음을 들려 준다." << '\n';
		cout << " 그리고 그 음을 번호로 맞힌다." << '\n';
		cout << "---------------------------------" << '\n';
		cout << " 준비하고 아무 키나 누른다." << '\n';
		cout << "-----------------" << '\n';
		cout << '\n';

		while (!_getch());

		for (int i = 0; i < 8; ++i) {
			cout << ' ' << soundName[i] << '(' << i + 1 << ')';
			Beep(sounds[i], 500);
		}

		cout << '\n';
		cout << "---------------------------------" << '\n';
		for (int i = 3; i > 0; --i) {
			cout << "\b\b\b" << i << "..";
			Sleep(1000);
		}

		system("cls");
		cout << "!!!준비!!!" << '\n';
		Beep(sounds[randSoundIdx], 500);

		//입력 왜 이따구 왜 안 받아지는 거지
		int input = 0;


		input = _getch() - '0';

		if (input - 1 == randSoundIdx) {
			cout << "잘하셨습니다!" << '\n';
		}
		else
			cout << "안타깝네요" << '\n';

		cout << "게임을 그만둘까요? (Y/N)" << '\n';

		char chInput = _getch();

		switch (chInput)
		{
		case 'y':
		case 'Y':
			isEnd = true;
			break;
		case 'n':
		case 'N':
			break;
		default:
			cout << "잘못 입력하셨습니다.";
			isEnd = true;
			break;
		}
	}
	
}