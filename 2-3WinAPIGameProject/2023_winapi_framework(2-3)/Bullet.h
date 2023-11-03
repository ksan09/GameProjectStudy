#pragma once
#include "Object.h"
class Bullet :
    public Object
{
public:
    Bullet();
    ~Bullet();
public:
    void Update()           override;
    void Render(HDC _dc)    override;
public:
    void SetDir(float _f) { m_fTheta = _f; }
    void SetDir(Vec2 _v) 
    { 
        m_vDir = _v; 
        m_vDir.Normalize();
    }
private:
    float m_fDir;
    float m_fTheta;
    Vec2 m_vDir;
};

