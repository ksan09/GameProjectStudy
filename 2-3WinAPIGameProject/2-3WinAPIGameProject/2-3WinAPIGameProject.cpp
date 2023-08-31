// 2-3WinAPIGameProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2-3WinAPIGameProject.h"
#include <string>
#include <time.h>
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
    if (!InitInstance (hInstance, nCmdShow))
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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground  = (HBRUSH)(GetStockObject(WHITE_BRUSH));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY23WINAPIGAMEPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

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
#include <time.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static wchar_t wstr[1000];
    static int count;
    switch (message)
    {
    case WM_CREATE:
    {
        count = 0;
    }
    break;
    case WM_LBUTTONDBLCLK:
        MessageBox(hWnd, L"마우스 왼쪽 버튼 더블클릭", L"메세지 박스", MB_OK);
    break;
    case WM_CHAR:
    {
        //wstring wstr = L"키 입력 감지";
        if (wParam == VK_BACK)
            count--;
        else
            wstr[count++] = wParam;
        wstr[count] = NULL;

        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //InvalidateRect();
#pragma region 주석처리한 수업내용들
        //// 연습 문제1
        //for (int x = 0; x < 17; ++x)
        //{
        //    MoveToEx(hdc, x * WINSIZEX / 16, 0, nullptr);
        //    LineTo(hdc, x * WINSIZEX / 16, WINSIZEY);
        //}
        //for (int y = 0; y < 10; ++y)
        //{
        //    MoveToEx(hdc, 0, WINSIZEY/9 * y, nullptr);
        //    LineTo(hdc, WINSIZEX, WINSIZEY/9 * y);
        //}
        //// 연습 문제2
        //for (int i = 0; i < 25; ++i)
        //{
        //    int left = (i % 5 * 70) + 100;
        //    int top = (i / 5 * 70) + 100;
        //
        //    if(i/5%2==0)
        //        Rectangle(hdc, left, top, left + 50, top + 50);
        //    else
        //        Ellipse(hdc, left, top, left + 50, top + 50);
        //}
        
        // 점, 선, 도형
        ////점
        //for (int i = 0; i < 1000; ++i)
        //    SetPixel(hdc, rand() % 100, rand() % 100, RGB(255, 0, 0));
        ////선
        //// 시작점
        //MoveToEx(hdc, 20, 20, nullptr);
        //// 끝점
        //LineTo(hdc, 200, 200);

        //// 텍스트 출력
        //// 1. Textout
        //wstring wstr = L"2-3 준이 바보\n준이 메롱";
        //TextOut(hdc, 10, 10, wstr.c_str(), wstr.length());
        //// 2. DrawText
        //RECT rt = { 50, 50, 500, 500 };
        //Rectangle(hdc, 50, 50, 500, 500);
        //DrawText(hdc, wstr.c_str(), wstr.length(), &rt, DT_RIGHT);

        // 펜 쓰는 법
        //HPEN hCyanpen = CreatePen(PS_SOLID, 10, RGB(0, 0, 255));
        //HPEN hDefaultpen = (HPEN)SelectObject(hdc, hCyanpen);
        //HBRUSH hMabrush = CreateSolidBrush(RGB(255, 0, 255));
        //HBRUSH hHatchBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 255, 0));
        //SelectObject(hdc, hHatchBrush);
        //Rectangle(hdc, 100, 100, 500, 300);
        //SelectObject(hdc, hCyanpen);
        //Rectangle(hdc, 100, 100, 500, 300);
        //
        //DeleteObject(hCyanpen);
        //DeleteObject(hMabrush);
        //DeleteObject(hHatchBrush);
#pragma endregion
        TextOut(hdc, 100, 100, wstr, wcslen(wstr));
        
            

        
          
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...



        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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
