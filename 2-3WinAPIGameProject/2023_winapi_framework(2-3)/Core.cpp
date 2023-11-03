#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"

bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	// === 1.변수 초기화 ===
	m_hWnd			= _hWnd;
	m_ptResolution	= _ptResolution;

	// === 2.더블 버퍼링 ===
	m_hDC		= GetDC(m_hWnd);
	// 1.생성
	m_hBackbit	= CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hBackDC	= CreateCompatibleDC(m_hDC);

	// 2.연결
	SelectObject(m_hBackDC, m_hBackbit);

	// 3.옮기기


	//

	// === 3. Manager Init ===
	PathMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	SceneMgr::GetInst()->Init();

	return true;
}

void Core::GameLoop()
{

	Update();
	Render();

}

void Core::Release()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_hBackDC);
	DeleteObject(m_hBackbit);

	// === Manager Release ===
	ResMgr::GetInst()->Release();
}

void Core::Update()
{
	// === Manager Update ===
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	SceneMgr::GetInst()->Update();

}

void Core::Render()
{
	// Clear
	PatBlt(m_hBackDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS);
	Rectangle(m_hBackDC, -1, -1, m_ptResolution.x+1, m_ptResolution.y+1);

	SceneMgr::GetInst()->Render(m_hBackDC);

	// cursor test
	POINT mousepos = KeyMgr::GetInst()->GetMousePos();
	static wchar_t mousebuf[100] = {};
	swprintf_s(mousebuf, L"Mouse: x %d, y: %d", mousepos.x, mousepos.y);
	TextOut(m_hBackDC, 10, 10, mousebuf, wcslen(mousebuf));
	
	// 옮기기
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_hBackDC, 0, 0, SRCCOPY);

}
