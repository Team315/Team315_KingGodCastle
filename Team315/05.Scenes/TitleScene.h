#pragma once
#include "Scene.h"
#include "../02.Object/SpriteObj.h"
#include "../02.Object/TextObj.h"

class TitleScene : public Scene
{
protected:
	SpriteObj* background;
	TextObj* titleText;

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