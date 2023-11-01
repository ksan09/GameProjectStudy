#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"

Monster::Monster()
	: m_fSpeed(100.f)
	, m_fMaxDist(50.f)
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_fDir(1.f)
	, m_iHp(5)
{
	
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vec2 vPos = GetPos();
	vPos.x += m_fSpeed * fDT * m_fDir;
	float fDist = abs(m_vCenterPos.x - vPos.x) - m_fMaxDist;
	if (fDist > 0.f)
	{
		// 방향 바꾸기
		m_fDir *= -1;
		vPos.x += fDist * m_fDir;
	}

	SetPos(vPos);

}
