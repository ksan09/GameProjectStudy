#pragma once

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};