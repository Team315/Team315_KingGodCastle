#pragma once
#include "Scene.h"
#include "Player/Evan.h"
#include "SpriteObj.h"
#include <vector>

class BattleScene : public Scene
{
protected:
	SpriteObj* background;
	Evan* evan;

public:
	BattleScene();
	virtual ~BattleScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};