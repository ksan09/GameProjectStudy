#include "pch.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Start_Scene.h"
#include "Game_Scene.h"

void SceneMgr::RegisterScene(const wstring& _sceneName, std::shared_ptr<Scene> _scene)
{
	m_mapScenes.insert(m_mapScenes.end(), { _sceneName, _scene });
}

void SceneMgr::LoadScene(const wstring& _sceneName)
{
	if (m_pCurScene != nullptr)
	{
		m_pCurScene->Release();
		m_pCurScene = nullptr;
	}

	auto iter = m_mapScenes.find(_sceneName);
	if (iter != m_mapScenes.end())
	{
		m_pCurScene = iter->second;
		m_pCurScene->Init();
	}
}

void SceneMgr::Init()
{
	m_pCurScene = nullptr;

	//¾À Ãß°¡
	RegisterScene(L"Start_Scene", std::make_shared<Start_Scene>());
	RegisterScene(L"Game_Scene", std::make_shared<Game_Scene>());

	//Ã¹ ¾À µî·Ï or ¾À Ã¼ÀÎÁö
	LoadScene(L"Start_Scene");
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}
