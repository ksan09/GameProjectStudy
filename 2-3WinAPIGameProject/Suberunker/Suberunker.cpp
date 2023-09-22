// Suberunker.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Suberunker.h"
#include <vector>
#include <time.h>

#define MAX_LOADSTRING 100
#define WINSIZEX 1280
#define WINSIZEY 720

#define RECT_RENDER(posX, posY, scaleX, scaleY) Rectangle(hdc, posX - scaleX / 2, posY - scaleY / 2, posX + scaleX / 2, posY + scaleY / 2)
#define RECT_MAKE(posX, posY, scaleX, scaleY) {posX - scaleX / 2, posY - scaleY / 2, posX + scaleX / 2, posY + scaleY / 2};

//obj
struct tObjInfo
{
    POINT pos;
    POINT scale;
};

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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SUBERUNKER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUBERUNKER));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUBERUNKER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SUBERUNKER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINSIZEX, WINSIZEY, nullptr, nullptr, hInstance, nullptr);

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
enum class MOVE_DIR
{
    IDLE, LEFT, RIGHT, UP, DOWN
};
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static tObjInfo Player = { {WINSIZEX / 2, WINSIZEY - 125}, {100, 100} };
    static std::vector<tObjInfo> vecobj;
    
    static MOVE_DIR eDir = MOVE_DIR::IDLE;
    static float fMoveSpeed = 20.0f;
    static int iDelay = 50;
    static int iScore = 0;

    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer(hWnd, 1, 10, nullptr);
        srand((unsigned int)time(NULL));
    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 'A':
        case VK_LEFT:
            eDir = MOVE_DIR::LEFT;
            break;
        case 'D':
        case VK_RIGHT:
            eDir = MOVE_DIR::RIGHT;
            break;
        default:
            break;
        }
    }
    break;
    case WM_KEYUP:
        eDir = MOVE_DIR::IDLE;
    break;
    case WM_TIMER:
    {
        if (iDelay >= 50)
        {
            tObjInfo temp = { {rand() % WINSIZEX, 0 }, { 50, 50 } };
            vecobj.push_back(temp);
            iDelay = rand() % 50;
        }
        else
            iDelay++;
        
        

        if (eDir == MOVE_DIR::LEFT)
        {
            Player.pos.x -= fMoveSpeed;
        }
        else if (eDir == MOVE_DIR::RIGHT)
        {
            Player.pos.x += fMoveSpeed;
        }

        for (size_t i = 0; i < vecobj.size();)
        {
            // 비 내려보내기
            vecobj[i].pos.y += 10;

            // 땅 닿으면 삭제
            RECT tempRt, playerRt, objRt;
            playerRt = RECT_MAKE(Player.pos.x, Player.pos.y, Player.scale.x, Player.scale.y);
            objRt = RECT_MAKE(vecobj[i].pos.x, vecobj[i].pos.y, vecobj[i].scale.x, vecobj[i].scale.y);
            if (vecobj[i].pos.y > WINSIZEY ||
                IntersectRect(&tempRt, &playerRt, &objRt))
            {
                vecobj.erase(vecobj.begin() + i);
                iScore++;
            }
            else
                ++i;
        }

        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HBRUSH hRedBrush = CreateSolidBrush(RGB(255, 100, 100));
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hRedBrush);

            // 비 내리기
            for (size_t i = 0; i < vecobj.size(); ++i)
            {
                // 비 그리기
                RECT_RENDER(vecobj[i].pos.x,
                    vecobj[i].pos.y,
                    vecobj[i].scale.x,
                    vecobj[i].scale.y);

                
            }
             
            //플레이어 드로우
            HBRUSH hPlayerBrush = CreateSolidBrush(RGB(100, 100, 255));
            SelectObject(hdc, hPlayerBrush);

            RECT_RENDER(Player.pos.x,
                        Player.pos.y,
                        Player.scale.x,
                        Player.scale.y);

            SelectObject(hdc, hDefaultBrush);
            wchar_t bufScore[32];
            _itow_s(iScore, bufScore, 10);
            TextOut(hdc, 10, 10, bufScore, _tcslen(bufScore));

            DeleteObject(hRedBrush);
            DeleteObject(hPlayerBrush);

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
