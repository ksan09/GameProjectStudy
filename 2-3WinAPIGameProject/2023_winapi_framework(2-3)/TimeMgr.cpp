#include "pch.h"
#include "TimeMgr.h"

void TimeMgr::Init()
{
	m_llPrevCount	= {};
	m_llFrequency	= {};
	m_llCurCount	= {};

	// ���� Ÿ�̸��� ���� �ð� ī��Ʈ? ƽ?
	// �̰ɷ� �ð��� �� ���� ����
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ��(1000��) ��ȯ.
	// ���� Ÿ�̸Ӱ� �����ϴ� ���ļ��� �˷����
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	//DT ���ϱ� <- ���� �ð��� ���
	m_llCurCount.QuadPart - m_llPrevCount.QuadPart;

	//to do
	m_llPrevCount = m_llCurCount;
}
