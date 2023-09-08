// 2-3WinAPIGameProject.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "2-3WinAPIGameProject.h"
#include <string>
#include <time.h>
#include <math.h>
using namespace std;

#define MAX_LOADSTRING 100
#define PROGRAM_TITLE L"������ ����"
#define WINSIZEX 1280
#define WINSIZEY 720

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    srand((unsigned int)time(NULL));

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY23WINAPIGAMEPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY23WINAPIGAMEPROJECT));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY23WINAPIGAMEPROJECT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    int iResolutionX = GetSystemMetrics(SM_CXSCREEN); //����
    int iResolutionY = GetSystemMetrics(SM_CYSCREEN); //����

    int iWinposX = iResolutionX / 2 - WINSIZEX / 2;
    int iWinposY = iResolutionY / 2 - WINSIZEY / 2;

    HWND hWnd = CreateWindowW(
        szWindowClass,
        L"������ ������",
        WS_OVERLAPPEDWINDOW,
        iWinposX,
        iWinposY,
        WINSIZEX,
        WINSIZEY,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    RECT rt = { iWinposX, iWinposY, iWinposX + WINSIZEX, iWinposY + WINSIZEY };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
    // ���
    MoveWindow(hWnd, iWinposX, iWinposY, rt.right - rt.left, rt.bottom - rt.top, true);
    // ����

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

double LengthPt(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
bool InCircle(int x, int y, int mx, int my, int radius)
{
    return (LengthPt(x, y, mx, my) < radius);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static POINT ptObjpos = { 100,100 };
    static POINT ptObjscale = { 100, 100 };
    static RECT rectview;
    //static HBRUSH hBrush, hDefaultBrush;
    static bool isKeyDown = false, isMove = false;
    static int mouseX, mouseY;
    static bool isClick = false;
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        mouseX = LOWORD(lParam);
        mouseY = HIWORD(lParam);

        isClick = true;
        SetTimer(hWnd, 1, 1, nullptr);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_LBUTTONUP:
    {
        isClick = false;
        KillTimer(hWnd, 1);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_LBUTTONDBLCLK:
    {
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_SIZE:
    {
        GetClientRect(hWnd, &rectview);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_CREATE:
        GetClientRect(hWnd, &rectview);
        //rectview = { 0, 0, 600, 600 };
        break;
    case WM_KEYUP:
        isKeyDown = false;
        //InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_TIMER:
    {
        double dist = LengthPt(ptObjpos.x, ptObjpos.y, mouseX, mouseY);
        if (dist <= 5)
            break;
        double dirX = (mouseX - ptObjpos.x) / dist;
        double dirY = (mouseY - ptObjpos.y) / dist;

        int speed = 10;
        ptObjpos.x += (int)(dirX * speed);
        ptObjpos.y += (int)(dirY * speed);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_KEYDOWN:
    {
#pragma region ��������

        //switch (wParam)
        //{
        //case VK_RETURN:
        //{
        //    isMove = !isMove;
        //    if (isMove)
        //    {
        //        SetTimer(hWnd, 1, 100, nullptr);
        //    }
        //    else
        //        KillTimer(hWnd, 1);
        //}
        //break;
        //case VK_LEFT:
        //    if (ptObjpos.x - ptObjscale.x / 2 > rectview.left)
        //    {
        //        ptObjpos.x -= 10;
        //        isKeyDown = true;
        //    }
        //    break;
        //case VK_RIGHT:
        //    if (ptObjpos.x + ptObjscale.x / 2 < rectview.right)
        //    {
        //        ptObjpos.x += 10;
        //        isKeyDown = true;
        //    }
        //    break;
        //default:
        //    break;
        //}
#pragma endregion

        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
#pragma region ��������


        //hBrush = CreateSolidBrush(RGB(240, 240, 255));
        //hDefaultBrush = CreateSolidBrush(RGB(255, 255, 255));
        
        //SelectObject(hdc, isKeyDown ? hBrush : hDefaultBrush);

        //if(isClick)
        //    Rectangle(hdc,
        //        ptObjpos.x - ptObjscale.x / 2,
        //        ptObjpos.y - ptObjscale.y / 2,
        //        ptObjpos.x + ptObjscale.x / 2,
        //        ptObjpos.y + ptObjscale.y / 2);
        //Ellipse(hdc,
        //    ptObjpos.x - ptObjscale.x / 2,
        //    ptObjpos.y - ptObjscale.y / 2,
        //    ptObjpos.x + ptObjscale.x / 2,
        //    ptObjpos.y + ptObjscale.y / 2);
#pragma endregion
        //�ؽ�Ʈ�� ��� �������� ���� �� �ֵ���
        if (isClick)
            TextOut(hdc, mouseX, mouseY, L"����", 2);
        TextOut(hdc, ptObjpos.x, ptObjpos.y, L"�׸���", 3);
        

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
