#include "pch.h"
#include "KeyMgr.h"
#include "Core.h"

void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
	m_ptMousePos = {};
}

void KeyMgr::Update()
{
	HWND hMainHwnd = GetFocus();
	if (hMainHwnd != nullptr)
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			if (GetAsyncKeyState(m_arrVKKey[i])) //Ű�� ���ȴ�.
			{
				if (m_vecKey[i].IsPrevCheck)
				{
					m_vecKey[i].eState = KEY_STATE::PRESS;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::DOWN;
				}
				m_vecKey[i].IsPrevCheck = true;

			}
			else // �� ���ȴ�.
			{
				if (m_vecKey[i].IsPrevCheck)
				{
					m_vecKey[i].eState = KEY_STATE::UP;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].IsPrevCheck = false;
			}
		}
		// Mouse
		GetCursorPos(&m_ptMousePos);
		// ��ũ������ ������� ��ǥ ����
		ScreenToClient(Core::GetInst()->GetHWnd(), &m_ptMousePos);
	}
	else // ALT + TAP
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			m_vecKey[i].IsPrevCheck = false;
			if (m_vecKey[i].eState == KEY_STATE::PRESS
				|| m_vecKey[i].eState == KEY_STATE::DOWN)
			{
				m_vecKey[i].eState = KEY_STATE::UP;
			}
			if (m_vecKey[i].eState == KEY_STATE::UP)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
	
}
