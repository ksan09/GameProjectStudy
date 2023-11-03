#include "pch.h"
#include "Player.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"

Player::Player()
	: m_pTex(nullptr)
{
	m_pTex = new Texture;
	wstring strFilePath = PathMgr::GetInst()->GetResPath();
	strFilePath += L"Texture\\plane.bmp";
	m_pTex->Load(strFilePath);
}

Player::~Player()
{
	if (m_pTex != nullptr)
		delete m_pTex;
}

void Player::Update()
{
	Vec2 vPos = GetPos();
	if (KEY_PRESS(KEY_TYPE::LEFT))
		vPos.x -= 200.f * fDT;
	if (KEY_PRESS(KEY_TYPE::RIGHT))
		vPos.x += 200.f * fDT;
	if (KEY_PRESS(KEY_TYPE::DOWN))
		vPos.y += 200.f * fDT;
	if (KEY_PRESS(KEY_TYPE::UP))
		vPos.y -= 200.f * fDT;

	if (KEY_DOWN(KEY_TYPE::SPACE))
		CreateBullet();
	SetPos(vPos);


}

void Player::CreateBullet()
{
	Bullet* pBullet = new Bullet;
	Vec2 vPos = GetPos();
	vPos.y -= GetScale().y / 2;
	pBullet->SetPos(vPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(Vec2(-1.f, -1.f));
	SceneMgr::GetInst()->GetCurScene()->AddObject(
		pBullet, OBJ_GROUP::BULLET);
}

void Player::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	//// 1. 그냥 옮기기
	//BitBlt(_dc
	//	,(int)(vPos.x - vScale.x), (int)(vPos.y - vScale.y)
	//	,width, height,
	//	m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);
	
	//// 2. 색상 빼기
	//TransparentBlt(_dc
	//	,(int)(vPos.x - vScale.x), (int)(vPos.y - vScale.y)
	//	,width, height,
	//	m_pTex->GetDC()
	//	, 0, 0, width, height, RGB(255, 0, 255));

	//// 3. 확대 축소
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x), (int)(vPos.y - vScale.y)
	//	, width, -height,
	//	m_pTex->GetDC()
	//	, 0, 0, width, height, SRCCOPY);

}
