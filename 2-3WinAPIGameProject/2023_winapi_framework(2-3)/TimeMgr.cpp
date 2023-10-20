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
	m_dT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) /
		(float)m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;

	//FPS
	m_framecount++;
	m_accFrameTime += m_dT; //�ð� ����
	if (m_accFrameTime >= 1.f) //1��
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
