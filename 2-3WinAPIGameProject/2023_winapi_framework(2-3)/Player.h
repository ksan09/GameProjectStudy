#pragma once
#include "Object.h"
class Player :
    public Object
{
public:
    Player();
    ~Player();
public:
    virtual void Update()           override;
    //virtual void Render(HDC _dc)    override;
};

