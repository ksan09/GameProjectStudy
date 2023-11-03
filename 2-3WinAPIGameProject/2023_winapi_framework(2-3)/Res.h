#pragma once
class Res
{
public:
	Res();
	~Res();
public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }
	const wstring& GetKey() const { return m_strKey; }
	const wstring& GetRelativePath() const { return m_strRelativePath; }
private:
	wstring m_strRelativePath;	// 상대 경로
	wstring m_strKey;			// 키값
};

