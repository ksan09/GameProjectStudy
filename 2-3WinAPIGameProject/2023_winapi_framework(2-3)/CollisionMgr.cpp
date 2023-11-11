#include "pch.h"
#include "CollisionMgr.h"

void CollisionMgr::Update()
{
}

void CollisionMgr::CheckGroup(OBJ_GROUP _eLeft, OBJ_GROUP _eRight)
{
	// 작은 것을 무조건 행으로 보겠다.
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	if (Row > Col)
		std::swap(Row, Col);

	// 만약에 체크가 이미 되어있다면?
	if (m_arrCheck[Row] && (1 << Col))
	{
		m_arrCheck[Row] &= ~(1 << Col);
	}

	m_arrCheck[Row] |= (1 << Col);
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJ_GROUP::END);

}