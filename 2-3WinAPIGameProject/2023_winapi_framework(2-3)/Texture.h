#pragma once
#include "Res.h"
class Texture :
    public Res
{
private:
    Texture();
    ~Texture();
    friend class ResMgr;
public:
    void Load(const wstring& _strFilePath);
    const HDC& GetDC()      const { return m_hDC; }
    const int& GetWidth()   const { return m_bitInfo.bmWidth; }
    const int& GetHeight()  const { return m_bitInfo.bmHeight; }
private:
    HDC     m_hDC;
    HBITMAP m_hBit;
    BITMAP  m_bitInfo;
};

