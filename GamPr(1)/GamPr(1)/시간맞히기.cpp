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
	cout << "|  시간맞히기게임 |" << endl;
	cout << "===================" << endl;
	cout << "==================================================================" << endl;
	cout << "설명 : 시간을 재는 게임입니다." << endl;
	cout << "처음 key와 나중에 누른 key 사이의 시간을 10초로 만들어놓았습니다." << endl;
	cout << "==================================================================" << endl;
	cout << "아무키나 누르세요." << endl;
	cout << "==================================================================" << endl;

}

void GameStart() {
	long long answerTime = 0, clickTime = 0;

	_getch();
	answerTime = time(NULL) + 10;
	cout << "!!!!!시작!!!!!\n\n";

	while (true) {
		if (_kbhit()) {
			clickTime = time(NULL);
			cout << "끝!!!\n\n";
			break;
		}
	}
	if (answerTime == clickTime) {
		cout << "축하합니다. 당신은 감각이 엄청나시군요?" << endl;
	}
	else if (answerTime > clickTime) {
		cout << "당신이 졌습니다." << endl;
		cout << "시간이 지나지 않았습니다." << endl;
	}
	else if (answerTime < clickTime) {
		cout << "당신이 졌습니다." << endl;
		cout << "시간이 지났습니다." << endl;
	}

	

}