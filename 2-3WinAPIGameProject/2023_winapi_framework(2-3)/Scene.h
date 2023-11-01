#pragma once
//#include "Object.h"
class Object;
class Scene
{
public:
	Scene();
	~Scene();
public:
	virtual void Init()				abstract;
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void Release();
public:
	void AddObject(Object* _pObj, OBJ_GROUP _eType)
	{
		m_vecObj[(UINT)_eType].push_back(_pObj);
	}

private:
	vector<Object*> m_vecObj[(UINT)OBJ_GROUP::END];
};

