#pragma once
class Texture;
class ResMgr
{
	SINGLE(ResMgr);
public:
	void Release();
public:
	Texture* TexLoad(const wstring& _strKey,
		const wstring& _strRelativePath);
	Texture* TexFind(const wstring& _strKey);
private:
	map<wstring, Texture*> m_mapTex;
};

