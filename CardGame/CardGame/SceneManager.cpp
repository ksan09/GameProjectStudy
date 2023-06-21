#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "console.h"

void SceneManager::RegisterScene(const wstring& sceneName, shared_ptr<Scene> scene)
{
	if (sceneName.empty())
		cout << "비어있음";
	else if (scene == NULL)
		cout << "내용물이 없음";

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
		//화면 전환 효과
		ToggleScreenRender();

		m_activeScene->Init();
	}
	else
		cout << "로드 실패!";
}

void SceneManager::Init()
{
	m_activeScene = NULL;
}

void SceneManager::Update(float dt)
{
	if (m_activeScene == NULL)
	{
		cout << "액티브 씬 없음";
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

void SceneManager::Release()
{
	m_activeScene = NULL;
}

void SceneManager::ToggleScreenRender()
{
	SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
	system("cls");
	int iCurmode = _setmode(_fileno(stdout), _O_U16TEXT);
	for (int x = 0; x < 118; x++)
	{
		Sleep(1);
		for (int y = 0; y < 30; y += 2)
		{
			SetColor((x/2) % 15 + 1, (int)COLOR::WHITE);
			GoToxy(x, y);
			wcout << L"   ██";
		}
		for (int y = 1; y < 29; y += 2)
		{
			SetColor((x / 2) % 15 + 1, (int)COLOR::WHITE);
			GoToxy(118-x, y);
			wcout << L"██   ";
		}
	}
	SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
	system("cls");
	iCurmode = _setmode(_fileno(stdout), O_TEXT);
}
