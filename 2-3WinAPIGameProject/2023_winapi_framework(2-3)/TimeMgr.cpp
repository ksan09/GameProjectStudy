#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"

void TimeMgr::Init()
{
	m_llPrevCount	= {};
	m_llFrequency	= {};
	m_llCurCount	= {};
	m_dT = 0.f;
	m_framecount = 0;
	m_accFrameTime = 0.f;
	m_fps = 0;

	// 현재 타이머의 지난 시간 카운트? 틱?
	// 이걸로 시간을 알 수는 없음
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수(1000만) 반환.
	// 현재 타이머가 동작하는 주파수를 알려줘요
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	//DT 구하기 <- 다음 시간에 계속
	m_dT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) /
		(float)m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;

	//FPS
	m_framecount++;
	m_accFrameTime += m_dT; //시간 누적
	if (m_accFrameTime >= 1.f) //1초
	{
		m_fps = m_framecount;
		m_accFrameTime = 0.f;
		m_framecount = 0;

		static wchar_t titlebuf[100] = {};
		swprintf_s(titlebuf, L"FPS: %d, DT: %f", m_fps, m_dT);
		SetWindowText(Core::GetInst()->GetHWnd(),
			titlebuf);
	}
}
