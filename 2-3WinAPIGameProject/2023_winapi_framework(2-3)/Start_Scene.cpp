#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"
#include "CollisionMgr.h"

void Start_Scene::Init()
{
	//Object 추가
	Vec2 vResolution = Core::GetInst()->GetResolution();
	Object* pObj = new Player;
	pObj->SetPos({ vResolution.x / 2, vResolution.y / 2 });
	pObj->SetScale({ 50.f, 50.f });
	AddObject(pObj, OBJ_GROUP::PLAYER);


	Monster* pMonsterObj = nullptr;
	// 크기나 움직일 거리, 몇마리 할건지
	int monstercnt = 10;
	float fMonsterScale = 50.f; // 기본 크기
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

	CollisionMgr::GetInst()->CheckGroup(OBJ_GROUP::BULLET,
		OBJ_GROUP::MONSTER);
}

void Start_Scene::Update()
{
	Scene::Update();
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
