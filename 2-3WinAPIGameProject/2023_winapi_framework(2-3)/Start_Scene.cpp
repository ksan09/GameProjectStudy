#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Monster.h"

void Start_Scene::Init()
{
	//Object 추가
	Vec2 vResolution = Core::GetInst()->GetResolution();

	Monster* pMonsterObj = nullptr;
	// 크기나 움직일 거리, 몇마리 할건지
	int monstercnt = 10;
	float fMonsterScale = 25.f; // 기본 크기
	float fMoveDist = 30.f; // 움직일 거리
	float fTerm = (vResolution.x - ((fMoveDist + fMonsterScale / 2.f) * 2)) / (monstercnt - 1);
	for (int i = 0; i < monstercnt; i++)
	{
		pMonsterObj = new Monster;
		pMonsterObj->SetScale(Vec2(fMonsterScale, fMonsterScale));
		pMonsterObj->SetPos(Vec2((fMoveDist + fMonsterScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDist(fMoveDist);
		AddObject(pMonsterObj, OBJ_GROUP::MONSTER);
	}
}
