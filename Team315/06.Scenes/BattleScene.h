#pragma once
#include "Scene.h"
#include "Player/Evan.h"
#include "Monster/Goblin00.h"
#include "SpriteObj.h"
#include "VertexArrayObj.h"
#include <vector>

class VertexArrayObj;
class BattleScene : public Scene
{
protected:
	Evan* evan;
	Goblin00* goblin00;
	VertexArrayObj* background;

public:
	BattleScene();
	virtual ~BattleScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateBackground(int cols, int rows, float qWidth, float qHeight);
	VertexArrayObj* GetBackground() { return background; }
};