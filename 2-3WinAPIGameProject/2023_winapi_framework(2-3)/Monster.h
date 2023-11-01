#pragma once
#include "Object.h"
class Monster :
    public Object
{
public:
    Monster();
    ~Monster();
public:
    virtual void Update()           override;  
public:
    void SetSpeed(float _f)         { m_fSpeed = _f; }
    void SetCenterPos(Vec2 _vPos)   { m_vCenterPos = _vPos; }
    void SetMoveDist(float _F)      { m_fMaxDist; }
    const float& GetSpeed() const   { return m_fSpeed; }
private:
    float   m_fDir;
    int     m_iHp;
    float   m_fSpeed;
    float   m_fMaxDist;
    Vec2    m_vCenterPos;
};

