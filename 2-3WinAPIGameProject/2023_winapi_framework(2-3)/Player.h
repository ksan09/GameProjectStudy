#pragma once
#include "Object.h"
class Texture;
class Player :
    public Object
{
public:
    Player();
    ~Player();
public:
    virtual void Update()           override;
    virtual void Render(HDC _dc)    override;
private:
    void CreateBullet();
private:
    Texture* m_pTex;
};

