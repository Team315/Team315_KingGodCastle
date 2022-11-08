#pragma once
#include "Scene.h"

class ToolScene : public Scene
{
protected:

public:
	ToolScene();
	virtual ~ToolScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};