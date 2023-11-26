#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Object.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "Core.h"
Animation::Animation()
	: m_pAnimator(nullptr)
	, m_CurFrame(0)
	, m_pTex(nullptr)
	, m_fAccTime(0.f)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_pAnimator->GetRepeatcnt() <= 0)
		return;
	m_fAccTime += fDT;
	// 누적한 시간이 내가 이 프레임에 진행한 시간을 넘어섰냐?
	if (m_fAccTime >= m_vecAnimFrame[m_CurFrame].fDuration)
	{
		// 일단 모은 시간에서 현재 진행한 시간을 빼고
		m_fAccTime -= m_vecAnimFrame[m_CurFrame].fDuration;
		++m_CurFrame; // 다음프레임으로 옮기기
		if (m_CurFrame >= m_vecAnimFrame.size()) // 한바퀴 돌게하고싶어
		{
			if (!m_pAnimator->GetRepeat())
				m_pAnimator->SetRepeatcnt();
			m_CurFrame = 0;
			m_fAccTime = 0.f;
		}

	}
}

void Animation::Render(HDC _dc)
{
	Object* pObj = m_pAnimator->GetObj();

	Vec2 vPos = pObj->GetPos(); // 센터값
	Vec2 vScale = pObj->GetScale();
	Vec2 vCenter = vPos;
	float angle = pObj->GetAngle();

	// 오프셋 적용
	vPos = vPos + m_vecAnimFrame[m_CurFrame].vOffset;
	

	POINT tPoint[3] = { 0 };
	float fx, fy, fxDest, fyDest;
	float fRadian = angle* M_PI / 180.f;

	float cosTheta = cosf(fRadian);
	float sinTheta = sinf(fRadian);
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0)
		{
			fx = -vScale.x / 2.f;
			fy = -vScale.y / 2.f;
		}
		else if (i == 1)
		{
			fx = vScale.x / 2.f;
			fy = -vScale.y / 2.f;
		}
		else if (i == 2)
		{
			fx = -vScale.x / 2.f;
			fy = vScale.y / 2.f;
		}
		fxDest = fx * cosTheta - fy * sinTheta;
		fyDest = fx * sinTheta + fy * cosTheta;
		tPoint[i].x = (LONG)fxDest + vCenter.x;
		tPoint[i].y = (LONG)fyDest + vCenter.y;
	}
	
	HDC alphaDC = CreateCompatibleDC(_dc);
	HBITMAP alphaBit = CreateCompatibleBitmap(_dc,
		Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y);
	SelectObject(alphaDC, alphaBit);
	PatBlt(alphaDC, 0, 0, Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y, WHITENESS);
	TransparentBlt(alphaDC
		, (int)(vPos.x - m_vecAnimFrame[m_CurFrame].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecAnimFrame[m_CurFrame].vSlice.y / 2.f)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecAnimFrame[m_CurFrame].vLT.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vLT.y)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y)
		, RGB(255, 0, 255));

	PlgBlt(_dc, tPoint, alphaDC,
		(int)(vPos.x - m_vecAnimFrame[m_CurFrame].vSlice.x / 2.f),
		(int)(vPos.y - m_vecAnimFrame[m_CurFrame].vSlice.y / 2.f),
		(int)(m_vecAnimFrame[m_CurFrame].vSlice.x),
		(int)(m_vecAnimFrame[m_CurFrame].vSlice.y),
		nullptr, 0, 0);

	DeleteObject(alphaBit);
	DeleteDC(alphaDC);
}

void Animation::Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, int _framecount, float _fDuration)
{
	m_pTex = _pTex;
	for (int i = 0; i < _framecount; ++i)
	{
		m_vecAnimFrame.push_back(tAnimFrame({ _vLT + _vStep * i,
			_vSliceSize, _fDuration,{0.f,0.f} }));
	}

}
