#pragma once
#include "Scene.h"
#include "MainSceneUI.h"

class MainScene : public Scene
{
protected:
	MainSceneUI* ui;

public:
	MainScene();
	virtual ~MainScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};