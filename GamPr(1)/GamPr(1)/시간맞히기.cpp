#include <iostream>
#include <Windows.h>
#include <conio.h> // console input output

using namespace std;

void Init();
void GameStart();

int main() 
{
	// get
	Init();
	GameStart();
}

void Init() {
	cout << "===================" << endl;
	cout << "|  �ð���������� |" << endl;
	cout << "===================" << endl;
	cout << "==================================================================" << endl;
	cout << "���� : �ð��� ��� �����Դϴ�." << endl;
	cout << "ó�� key�� ���߿� ���� key ������ �ð��� 10�ʷ� �������ҽ��ϴ�." << endl;
	cout << "==================================================================" << endl;
	cout << "�ƹ�Ű�� ��������." << endl;
	cout << "==================================================================" << endl;

}

void GameStart() {
	long long answerTime = 0, clickTime = 0;

	_getch();
	answerTime = time(NULL) + 10;
	cout << "!!!!!����!!!!!\n\n";

	while (true) {
		if (_kbhit()) {
			clickTime = time(NULL);
			cout << "��!!!\n\n";
			break;
		}
	}
	if (answerTime == clickTime) {
		cout << "�����մϴ�. ����� ������ ��û���ñ���?" << endl;
	}
	else if (answerTime > clickTime) {
		cout << "����� �����ϴ�." << endl;
		cout << "�ð��� ������ �ʾҽ��ϴ�." << endl;
	}
	else if (answerTime < clickTime) {
		cout << "����� �����ϴ�." << endl;
		cout << "�ð��� �������ϴ�." << endl;
	}

	

}