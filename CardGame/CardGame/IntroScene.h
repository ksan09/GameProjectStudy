#pragma once
#include "pch.h"
#include "Scene.h"

class IntroScene : public Scene
{
public:
	IntroScene();
	virtual ~IntroScene();

public:
	void Init()				override;
	void Update(float dt)	override;
	void Render()			override;

private:
	void TitleRender();
	void SelectUIRender(bool select, int posY, wstring str[3]);
	int startIdx;
	int maxIdx;


};

