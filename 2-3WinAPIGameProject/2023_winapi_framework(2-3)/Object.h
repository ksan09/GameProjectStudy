#pragma once
class Collider;
class Object
{
public:
	Object();
	~Object();
public:
	virtual void Update(); // abstract
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc);
public:
	Collider* GetCollider() const	{ return m_pCol; }
	void SetPos(Vec2 _vPos)			{ m_vPos = _vPos;		}
	void SetScale(Vec2 _vScale)		{ m_vScale = _vScale;	}
	const Vec2& GetPos()	const	{ return m_vPos;		}
	const Vec2& GetScale()	const	{ return m_vScale;		}
public:
	void CreateCollider();
	void Component_Render(HDC _dc);
private:
	// 위치, 크기
	Vec2 m_vPos;
	Vec2 m_vScale;
	Collider* m_pCol;
};

