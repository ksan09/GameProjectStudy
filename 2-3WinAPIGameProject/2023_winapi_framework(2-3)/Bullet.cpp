#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"

Bullet::Bullet()
	: m_fDir(-1.f) // -1(À§ÂÊ)
	, m_fTheta(0)
	, m_vDir(Vec2(0.f, 0.f))
{
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
	CIRCLE_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
}
