#pragma once
class Object;
class Collider
{
public:
	Collider();
	~Collider();
public:
	void FinalUpdate();
	void Render(HDC _dc);
public:
	void SetScale(Vec2 _vScale)
	{
		m_vScale = _vScale;
	}
	void SetOffsetPos(Vec2 _vOffsetpos)
	{
		m_vOffsetPos = _vOffsetpos;
	}
	const Vec2& GetScale() const
	{
		return m_vScale;
	}
	const Vec2& GetOffsetpos() const
	{
		return m_vOffsetPos;
	}
private:
	Object* m_pOwner;
	Vec2 m_vOffsetPos;
	Vec2 m_vFinalPos;
	Vec2 m_vScale;
	friend class Object;
};

