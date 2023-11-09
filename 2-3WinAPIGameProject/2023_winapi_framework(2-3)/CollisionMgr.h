#pragma once
class CollisionMgr
{
	SINGLE(CollisionMgr);
public:
	void Update();
	void CheckGroup(OBJ_GROUP _eLeft, OBJ_GROUP _eRight);
	void CheckReset();
private:
	UINT m_arrCheck[(UINT)OBJ_GROUP::END];
};

