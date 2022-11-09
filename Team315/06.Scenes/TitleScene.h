#pragma once
#include "Scene.h"
#include "SpriteObj.h"
#include "TextObj.h"

class TitleScene : public Scene
{
protected:
	SpriteObj* background;
	TextObj* titleText;
	float duration;
	float timer;

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};