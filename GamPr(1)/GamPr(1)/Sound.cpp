#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>

#include "resource.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

int main()
{
	//1.���ҽ� �̸�, 2. �ڵ�, 3. �÷���
	//- ���� ��ü�� �ҷ����� ���
	//- ���ҽ� ��ü�� �ҷ����� ���
	PlaySound(TEXT("explosing.wav"), nullptr, SND_FILENAME | SND_LOOP | SND_ASYNC);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), nullptr, SND_RESOURCE | SND_LOOP | SND_ASYNC);
	_getch();
}