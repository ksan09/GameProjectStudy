#pragma once
#include "Scene.h"

class ClearScene : public Scene
{
public:
	ClearScene();
	virtual ~ClearScene();

public:
	void Init()				override;
	void Update(float dt)	override;
	void Render()			override;
};

