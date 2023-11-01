#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Monster.h"

void Start_Scene::Init()
{
	//Object �߰�
	Vec2 vResolution = Core::GetInst()->GetResolution();

	Monster* pMonsterObj = nullptr;
	// ũ�⳪ ������ �Ÿ�, ��� �Ұ���
	int monstercnt = 10;
	float fMonsterScale = 25.f; // �⺻ ũ��
	float fMoveDist = 30.f; // ������ �Ÿ�
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
