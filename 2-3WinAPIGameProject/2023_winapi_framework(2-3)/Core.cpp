#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"

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
	m_obj.SetPos(Vec2({ _ptResolution.x / 2, _ptResolution.y / 2 }));
	m_obj.SetScale(Vec2({ 150, 150 }));

	// === 3. Manager Init ===
	TimeMgr::GetInst()->Init();

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
}

void Core::Update()
{
	// === Manager Update ===
	TimeMgr::GetInst()->Update();

	Vec2 vPos = m_obj.GetPos();
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		vPos.x -= 1000.f * fDT;
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		vPos.x += 1000.f * fDT;

	m_obj.SetPos(vPos);
}

void Core::Render()
{
	// Clear
	PatBlt(m_hBackDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS);

	Rectangle(m_hBackDC, -1, -1, m_ptResolution.x+1, m_ptResolution.y+1);

	Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();
	RECT_RENDER(vPos.x, vPos.y,
				vScale.x, vScale.y, m_hBackDC);
	
	// 옮기기
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_hBackDC, 0, 0, SRCCOPY);

}
