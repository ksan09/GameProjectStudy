#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"

BaseWindow::BaseWindow(POINT _ptResoulution)
	: m_hInst(0)
	, m_hWnd(0)
    , m_ptResolution(_ptResoulution)
{
}

BaseWindow::~BaseWindow()
{
}

int BaseWindow::Run(HINSTANCE _hInstance, LPWSTR _lpCmdLine, int _nCmdShow)
{
    m_hInst = _hInstance;

    MyRegisterClass();
    WindowCreate();
    WindowShow(_nCmdShow);
    WindowUpdate();

    if (!Core::GetInst()->Init(m_hWnd, m_ptResolution))
    {
        MessageBox(m_hWnd, L"Core Error",
            L"ERROR", MB_OK);
    }

    return MessageLoop();
}

ATOM BaseWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = BaseWindow::WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = m_hInst;
    wcex.hIcon          = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MY2023WINAPIFRAMEWORK23));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = WINDOW_CLASS_NAME;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BaseWindow::WindowCreate()
{
    int iWinposx = GetSystemMetrics(SM_CXSCREEN) / 2 - m_ptResolution.x / 2;
    int iWinposy = GetSystemMetrics(SM_CYSCREEN) / 2 - m_ptResolution.y / 2;

    m_hWnd = CreateWindowW(
        WINDOW_CLASS_NAME,
        L"2-3 Game Framework",
        WS_OVERLAPPEDWINDOW,
        iWinposx, 
        iWinposy, 
        m_ptResolution.x, 
        m_ptResolution.y, 
        nullptr, 
        nullptr, 
        m_hInst, 
        nullptr);

    RECT rt = { iWinposx, iWinposy, iWinposx + m_ptResolution.x, iWinposy + m_ptResolution.y };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    MoveWindow(m_hWnd, iWinposx, iWinposy, rt.right - rt.left, rt.bottom - rt.top, true);
}

void BaseWindow::WindowShow(int _nCmdShow)
{
    ShowWindow(m_hWnd, _nCmdShow);
}

void BaseWindow::WindowUpdate()
{
    UpdateWindow(m_hWnd);
}

LRESULT BaseWindow::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }
    return 0;
}

int BaseWindow::MessageLoop()
{
    MSG msg;
    memset(&msg, 0, sizeof(msg));

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //Core 게임 루프 진행
            Core::GetInst()->GameLoop();
        }
    }

    Core::GetInst()->Release();
    return (int)msg.wParam;
}
