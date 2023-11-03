#pragma once
#include <assert.h>

class Vec2
{
public:
	Vec2();
	~Vec2();
	Vec2(float _x, float _y);
	Vec2(int _x, int _y);
	Vec2(POINT _pt);
	Vec2(const Vec2& _vec);
public:
	float Length() { return sqrt(pow(x, 2) + pow(y, 2)); }
	Vec2& Normalize()
	{
		float fLen = Length();
		assert(fLen != 0.f);
		x /= fLen;
		y /= fLen;
		return *this;
	}

public:
	float x;
	float y;
};

