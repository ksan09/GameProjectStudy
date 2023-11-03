#include "pch.h"
#include "ResMgr.h"
#include "PathMgr.h"
#include "Texture.h"

void ResMgr::Release()
{
	map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTex.begin(); iter != m_mapTex.end(); ++iter)
		delete iter->second;
}

Texture* ResMgr::TexLoad(const wstring& _strKey, const wstring& _strRelativePath)
{
	Texture* pTex = TexFind(_strKey);
	if (pTex != nullptr)
		return pTex;

	wstring strFilePath = PathMgr::GetInst()->GetResPath();
	strFilePath += _strRelativePath;

	pTex = new Texture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert({ _strKey, pTex });

	return pTex;
}

Texture* ResMgr::TexFind(const wstring& _strKey)
{
	auto iter = m_mapTex.find(_strKey);
	if (iter != m_mapTex.end())
		return iter->second;
	return nullptr;
}
