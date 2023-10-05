#pragma once
class BaseWindow
{
public:
	BaseWindow(POINT _ptResoulution);
	~BaseWindow();

public:
	// 전역 변수:
	int						Run(HINSTANCE _hInstance, LPWSTR _lpCmdLine, int _nCmdShow);
	ATOM					MyRegisterClass();
	void					WindowCreate();
	void					WindowShow(int _nCmdShow);
	void					WindowUpdate();
	static LRESULT CALLBACK	WndProc(HWND _hWnd, UINT message,WPARAM _wParam, LPARAM _lParam);
	int						MessageLoop();

private:
	HINSTANCE	m_hInst;	// 현재 인스턴스입니다.
	HWND		m_hWnd;
	POINT		m_ptResolution;
};

