#pragma once
#include "Scene.h"
#include "Player/Evan.h"
#include "Monster/Goblin00.h"
#include "SpriteObj.h"
#include <vector>

class BattleSceneUI;

class BattleScene : public Scene
{
protected:
	BattleSceneUI* ui;
	SpriteObj* background;
	Evan* evan;
	Goblin00* goblin00;

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