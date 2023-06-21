#pragma once
#include "Scene.h"

enum class ExplainState
{
	Menu,
	AttackCard,
	DefenseCard,
	GameRule,
};

class ExplainScene : public Scene
{
public:
	ExplainScene();
	virtual ~ExplainScene();

public:
	void Init()				override;
	void Update(float dt)	override;
	void Render()			override;

private:
	void SelectUIRender(bool select, int posY, wstring str[3]);
	ExplainState state;
	int startIdx;
	int maxIdx;
};

