#pragma once
class Scene;
class SceneMgr
{
	SINGLE(SceneMgr);
public:
	void RegisterScene(const wstring& _sceneName, std::shared_ptr<Scene> _scene);
	void LoadScene(const wstring& _sceneName);
public:
	void Init();
	void Update();
	void Render(HDC _dc);
private:
	std::shared_ptr<Scene> m_pCurScene; // ÇöÀç¾À
	map<wstring, std::shared_ptr<Scene>> m_mapScenes; // ÀÚ·á±¸Á¶ ¸ÊÀ¸·Î ¾À °ü¸®
};

