#pragma once
class BaseWindow
{
public:
	BaseWindow(POINT _ptResoulution);
	~BaseWindow();

public:
	// ���� ����:
	int						Run(HINSTANCE _hInstance, LPWSTR _lpCmdLine, int _nCmdShow);
	ATOM					MyRegisterClass();
	void					WindowCreate();
	void					WindowShow(int _nCmdShow);
	void					WindowUpdate();
	static LRESULT CALLBACK	WndProc(HWND _hWnd, UINT message,WPARAM _wParam, LPARAM _lParam);
	int						MessageLoop();

private:
	HINSTANCE	m_hInst;	// ���� �ν��Ͻ��Դϴ�.
	HWND		m_hWnd;
	POINT		m_ptResolution;
};

