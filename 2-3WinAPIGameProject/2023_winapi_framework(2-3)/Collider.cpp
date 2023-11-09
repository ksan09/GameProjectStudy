#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "Core.h"
#include "SelectGDI.h"

Collider::Collider()
	: m_pOwner(nullptr)
	, m_vScale(Vec2(40.f, 40.f))
{
}

Collider::~Collider()
{
}

void Collider::FinalUpdate()
{
	// object를 따라가기
	Vec2 vPos = m_pOwner->GetPos();
	m_vFinalPos = vPos + m_vOffsetPos;
}

void Collider::Render(HDC _dc)
{
	SelectGDI pen(_dc, PEN_TYPE::GREEN);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);
	RECT_RENDER(
		m_vFinalPos.x
		, m_vFinalPos.y
		, m_vScale.x
		, m_vScale.y
		, _dc);
}
