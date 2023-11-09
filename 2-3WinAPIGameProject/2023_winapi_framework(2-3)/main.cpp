#include "pch.h"
#include "BaseWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 감지
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);

    // 감지한 곳에 브레이크
    //_CrtSetBreakAlloc(1);

    BaseWindow game({ WINDOW_WIDTH, WINDOW_HEIGHT });
    game.Run(hInstance, lpCmdLine, nCmdShow);

}