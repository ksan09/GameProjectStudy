#include <iostream>
#include <fstream>
#include "Stage.h"
#include "Define.h"
using namespace std;

Stage::Stage()
	: m_tStart{}, m_tEnd{}, m_cStage{}
{
}

Stage::~Stage()
{
}

bool Stage::Init(const char* _pFilename)
{
	ifstream readFile;
	if (readFile.is_open())
		return false;

	readFile.open(_pFilename);
	for (int i = 0; i < MAP_Y; ++i)
	{
		readFile.clear();
		// 1: 목적지 담을 곳 / 2. 스트림 사이즈
		readFile.getline(m_cStage[i], MAP_X + 1);
		for (int j = 0; j < MAP_X; ++j)
		{
			if (m_cStage[i][j] == (char)STAGE_TYPE::START)
			{
				m_tStart.x = j;
				m_tStart.y = i;
			}
			else if (m_cStage[i][j] == (char)STAGE_TYPE::END)
			{
				m_tEnd.x = j;
				m_tEnd.y = i;
			}
		}
	}

	return true;
}

void Stage::Render()
{
	for (int i = 4; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (m_cStage[i][j] == (char)STAGE_TYPE::WALL)
				cout << "■";
			else if (m_cStage[i][j] == (char)STAGE_TYPE::ROAD)
				cout << " ";
			else if (m_cStage[i][j] == (char)STAGE_TYPE::START)
				cout << "☆";
			else if (m_cStage[i][j] == (char)STAGE_TYPE::END)
				cout << "※";
			else if (m_cStage[i][j] == (char)STAGE_TYPE::COIN)
				cout << "⊙";
		}
		cout << '\n';
	}
}
