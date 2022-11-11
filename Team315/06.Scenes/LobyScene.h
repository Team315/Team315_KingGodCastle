#pragma once
#include "Scene.h"
#include <vector>

class LobySceneUI;
class SpriteObj;

class LobyScene : public Scene
{
protected:
	LobySceneUI* ui;
	vector<SpriteObj*> backgrounds;
	int tabSize;
	int currentBackground;

public:
	LobyScene();
	virtual ~LobyScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	void DrawBackground(RenderWindow& window);
};