#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>

#include "resource.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

int main()
{
	//1.리소스 이름, 2. 핸들, 3. 플래그
	//- 파일 자체를 불러오는 방법
	//- 리소스 자체를 불러오는 방법
	PlaySound(TEXT("explosing.wav"), nullptr, SND_FILENAME | SND_LOOP | SND_ASYNC);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), nullptr, SND_RESOURCE | SND_LOOP | SND_ASYNC);
	_getch();
}