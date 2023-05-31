#include <iostream>
#include "Core.h"

using namespace std;

int main()
{
	// Core((GameManager) 초기화
	if (!Core::GetInst()->Init())
	{
		// 종료
		cout << "게임 초기화 실패!" << '\n';
		Core::GetInst()->DestroyInst();
		return 0;
	}

	// Core((GameManager) 게임 구동
	Core::GetInst()->Run();

	// Core((GameManager) 끄기도 해야됨
	Core::GetInst()->DestroyInst();

}