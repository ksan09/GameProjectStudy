#include <iostream>
#include "Core.h"

using namespace std;

int main()
{
	// Core((GameManager) �ʱ�ȭ
	if (!Core::GetInst()->Init())
	{
		// ����
		cout << "���� �ʱ�ȭ ����!" << '\n';
		Core::GetInst()->DestroyInst();
		return 0;
	}

	// Core((GameManager) ���� ����
	Core::GetInst()->Run();

	// Core((GameManager) ���⵵ �ؾߵ�
	Core::GetInst()->DestroyInst();

}