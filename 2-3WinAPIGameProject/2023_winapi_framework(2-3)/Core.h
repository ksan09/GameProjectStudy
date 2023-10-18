#pragma once
#include "define.h"
#include "Object.h"
/*
* �̱���: ��ü�� �ν��Ͻ��� ���� 1���� �����Ǵ� ����
* - ��� ������ ������ �����ؾ� ��
* 
* ���̳��� �̱���: 
* ����) ���� ���� �� �����ϰ� ����, �ʿ��� �� ������.
* ����) �޸𸮰� ���� ������, ���� ���������
* 
* ���� �̱���
* ����) �޸𸮰� �����Ϳ� ����, ���� �������� ��
* ����) ������ �ʾƵ� ����
*/

class Core // GameManager
{
	SINGLE(Core);
public:
	bool Init(HWND _hWnd, POINT _ptResolution);
	void GameLoop();
	void Release();
private:
	void Update();
	void Render();
private:
	HWND m_hWnd;
	POINT m_ptResolution;
	HDC m_hDC;
	Object m_obj;
};

