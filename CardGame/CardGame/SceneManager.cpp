#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::RegisterScene(const wstring& sceneName, shared_ptr<Scene> scene)
{
	if (sceneName.empty())
		cout << "�������";
	else if (scene == NULL)
		cout << "���빰�� ����";

	if (sceneName.empty() || scene == NULL)
		return;

	m_sceneContainer.insert(m_sceneContainer.end(), pair<wstring, shared_ptr<Scene>>(sceneName, scene));
}

void SceneManager::LoadScene(const wstring& sceneName)
{
	auto it = m_sceneContainer.find(sceneName);
	if (it != m_sceneContainer.end())
	{
		m_activeScene = it->second;
		m_activeScene->Init();
	}
	else
		cout << "�ε� ����!";
}

void SceneManager::Init()
{
	m_activeScene = NULL;
}

void SceneManager::Update(float dt)
{
	if (m_activeScene == NULL)
	{
		cout << "��Ƽ�� �� ����";
		return;
	}

	m_activeScene->Update(dt);
}

void SceneManager::Render()
{
	if (m_activeScene == NULL)
		return;

	m_activeScene->Render();
}
