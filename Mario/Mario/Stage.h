#pragma once
#include "Define.h"

class Stage
{
public:
	Stage();
	~Stage();

	// 벽을 찍을 수 있어야 함 render
	// 벽을 업데이트해줘야 함

	// 맵을 들고 있어야함
private:
	char m_cStage[MAP_Y][MAP_X];
	POINT m_tStart;
	POINT m_tEnd;

public:
	POINT GetStart() { return m_tStart; }
	POINT GetEnd() { return m_tEnd; }
	char GetStage(int x, int y) { return m_cStage[y][x]; }

public:
	bool Init(const char* _pFilename);
	void Render();
};