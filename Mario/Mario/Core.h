#pragma once
#include "Define.h"

static class Core
{
private:
	static Core* m_pInst;
public:
	static Core* GetInst()
	{
		if (m_pInst == nullptr)
			m_pInst = new Core;
		return m_pInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	Core();
	~Core();

public:
	bool Init();
	void Run();
	int MenuDraw();
};