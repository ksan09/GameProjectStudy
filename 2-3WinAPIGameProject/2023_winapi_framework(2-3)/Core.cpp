#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"

bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd			= _hWnd;
	m_ptResolution	= _ptResolution;

	m_hDC			= GetDC(m_hWnd);
	m_obj.SetPos(Vec2({ _ptResolution.x / 2, _ptResolution.y / 2 }));
	m_obj.SetScale(Vec2({ 150, 150 }));

	// === Manager Init ===
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
}

void Core::Update()
{
	TimeMgr::GetInst()->Update();

	Vec2 vPos = m_obj.GetPos();
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		vPos.x -= 0.01f;
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		vPos.x += 0.01f;

	m_obj.SetPos(vPos);
}

void Core::Render()
{
	Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();
	RECT_RENDER(vPos.x, vPos.y,
				vScale.x, vScale.y, m_hDC);
}
