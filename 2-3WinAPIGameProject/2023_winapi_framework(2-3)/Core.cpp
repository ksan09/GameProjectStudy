#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "CollisionMgr.h"

bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	// === 1.���� �ʱ�ȭ ===
	m_hWnd			= _hWnd;
	m_ptResolution	= _ptResolution;

	// === 2.���� ���۸� ===
	m_hDC		= GetDC(m_hWnd);
	// 1.����
	m_hBackbit	= CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hBackDC	= CreateCompatibleDC(m_hDC);

	// 2.����
	SelectObject(m_hBackDC, m_hBackbit);

	// 3.�ű��

	CreateGDI();

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
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
		DeleteObject(m_arrBrush[i]);
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
		DeleteObject(m_arrPen[i]);

	// === Manager Release ===
	ResMgr::GetInst()->Release();
}

void Core::CreateGDI()
{
	// HOLLOW
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));
	//RED GREEN BLUE PEN
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}

void Core::Update()
{
	// === Manager Update ===
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	SceneMgr::GetInst()->Update();
	CollisionMgr::GetInst()->Update();

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
	
	// �ű��
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_hBackDC, 0, 0, SRCCOPY);

}
