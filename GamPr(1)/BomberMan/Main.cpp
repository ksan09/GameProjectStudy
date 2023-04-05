#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
	//system("calc");
	//system("notepad");

	//system("title Bombman");
	//SetConsoleTitle(TEXT("2-3 Bombman"));

	system("mode con cols=50 lines=50 | title Bombman");
	//exit(0)

	_getch();
}