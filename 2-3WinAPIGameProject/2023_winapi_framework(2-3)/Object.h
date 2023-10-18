#pragma once
class Object
{
public:
	Object();
	~Object();
public:
	void SetPos(Vec2 _vPos)			{ m_vPos = _vPos;		}
	void SetScale(Vec2 _vScale)		{ m_vScale = _vScale;	}
	const Vec2& GetPos()	const	{ return m_vPos;		}
	const Vec2& GetScale()	const	{ return m_vScale;		}
private:
	// ��ġ, ũ��
	Vec2 m_vPos;
	Vec2 m_vScale;
};

