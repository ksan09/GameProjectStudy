#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"

Bullet::Bullet()
	: m_fDir(-1.f) // -1(위쪽)
	, m_fTheta(0)
	, m_vDir(Vec2(0.f, 0.f))
	, m_pTex(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Bullet", L"Texture\\Bullet.bmp");
	CreateCollider();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();
	vPos.y += 600.f * fDT * m_vDir.x;
	vPos.x += 600.f * fDT * m_vDir.y;
	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	//// 1. 그냥 옮기기
	//BitBlt(_dc
	//	,(int)(vPos.x - vScale.x), (int)(vPos.y - vScale.y)
	//	,width, height,
	//	m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	// 2. 색상 빼기
	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x), (int)(vPos.y - vScale.y)
		, width, height,
		m_pTex->GetDC()
		, 0, 0, width, height, RGB(255, 0, 255));

	Component_Render(_dc);
}
