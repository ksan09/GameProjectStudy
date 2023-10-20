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
public:
	const HWND& GetHWnd() const
	{
		return m_hWnd;
	}
private:
	void Update();
	void Render();
private:
	HWND m_hWnd;			// ���� ������ �ڵ�
	HDC m_hDC;				// ���� ������ DC
	HDC m_hBackDC;			// �� ���� DC
	HBITMAP m_hBackbit;		// �� ��Ʈ��
	POINT m_ptResolution;
	Object m_obj;
};

