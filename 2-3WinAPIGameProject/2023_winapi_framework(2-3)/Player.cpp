#include "pch.h"
#include "Player.h"
#include "TimeMgr.h"
#include "KeyMgr.h"

Player::Player()
{
}

Player::~Player()
{
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
	SetPos(vPos);


}

//void Player::Render(HDC _dc)
//{
//
//
//}
