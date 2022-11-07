#pragma once
#include "Scene.h"

class Button;

class SceneDev1 : public Scene
{
protected:
	Button* button;

public:
	SceneDev1();
	virtual ~SceneDev1();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};