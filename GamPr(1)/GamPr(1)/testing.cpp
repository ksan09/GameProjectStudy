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
		string soundName[8] = { "��", "��", "��", "��", "��", "��", "��", "��" };
		double sounds[8] = { 523.25, 587.33, 659.26, 698.46, 783.99, 880, 987.77, 1046.5 };

		system("cls");

		cout << "------------------" << '\n';
		cout << "| ���� ���� ���� |" << '\n';
		cout << "------------------" << '\n';
		cout << "���� : ó���� 8���踦 ��� �ְ�," << '\n';
		cout << " ������ 8�� �� �� ���� ���� ��� �ش�." << '\n';
		cout << " �׸��� �� ���� ��ȣ�� ������." << '\n';
		cout << "---------------------------------" << '\n';
		cout << " �غ��ϰ� �ƹ� Ű�� ������." << '\n';
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
		cout << "!!!�غ�!!!" << '\n';
		Beep(sounds[randSoundIdx], 500);

		//�Է� �� �̵��� �� �� �޾����� ����
		int input = 0;


		input = _getch() - '0';

		if (input - 1 == randSoundIdx) {
			cout << "���ϼ̽��ϴ�!" << '\n';
		}
		else
			cout << "��Ÿ���׿�" << '\n';

		cout << "������ �׸��ѱ��? (Y/N)" << '\n';

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
			cout << "�߸� �Է��ϼ̽��ϴ�.";
			isEnd = true;
			break;
		}
	}
	
}