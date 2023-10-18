#include "pch.h"
#include "TimeMgr.h"

void TimeMgr::Init()
{
	m_llPrevCount	= {};
	m_llFrequency	= {};
	m_llCurCount	= {};

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
	m_llCurCount.QuadPart - m_llPrevCount.QuadPart;

	//to do
	m_llPrevCount = m_llCurCount;
}
