#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"

Object::Object()
	: m_vPos{}
	, m_vScale{}
	, m_pCol(nullptr)
{
}

Object::~Object()
{
	if (m_pCol != nullptr)
	{
		delete m_pCol;
	}
}

void Object::Update()
{
	
}

void Object::FinalUpdate()
{
	if (m_pCol)
		m_pCol->FinalUpdate();
}

void Object::Render(HDC _dc)
{
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
}

void Object::CreateCollider()
{
	m_pCol = new Collider();
	m_pCol->m_pOwner = this;
}

void Object::Component_Render(HDC _dc)
{
	if (m_pCol != nullptr)
		m_pCol->Render(_dc);
}
