#pragma once
#include "define.h"
struct tKeyInfo
{
	KEY_STATE eState;
	bool IsPrevCheck;
};

class KeyMgr
{
	SINGLE(KeyMgr);
public:
	void Init();
	void Update();
private:
	vector<tKeyInfo> m_vecKey;
};

