// 2-3WinAPIGameProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2-3WinAPIGameProject.h"
#include <string>
#include <time.h>
#include <math.h>
using namespace std;

#define MAX_LOADSTRING 100
#define PROGRAM_TITLE L"강산의 게임"
#define WINSIZEX 1280
#define WINSIZEY 720

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY23WINAPIGAMEPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY23WINAPIGAMEPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    int iResolutionX = GetSystemMetrics(SM_CXSCREEN); //높이
    int iResolutionY = GetSystemMetrics(SM_CYSCREEN); //높이

    int iWinposX = iResolutionX / 2 - WINSIZEX / 2;
    int iWinposY = iResolutionY / 2 - WINSIZEY / 2;

    HWND hWnd = CreateWindowW(
        szWindowClass,
        L"강산의 윈도우",
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
    // 계산
    MoveWindow(hWnd, iWinposX, iWinposY, rt.right - rt.left, rt.bottom - rt.top, true);
    // 세팅

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
#pragma region 이전수업

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
#pragma region 이전수업


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
        //텍스트도 가운데 맞춤으로 나올 수 있도록
        if (isClick)
            TextOut(hdc, mouseX, mouseY, L"강산", 2);
        TextOut(hdc, ptObjpos.x, ptObjpos.y, L"겜마고", 3);
        

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

// 정보 대화 상자의 메시지 처리기입니다.
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
