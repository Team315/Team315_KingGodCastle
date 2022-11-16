#pragma once
#include "Scene.h"
#include "Player/Evan.h"
#include "Monster/Goblin00.h"
#include "Player/Dummy.h"
#include "VertexArrayObj.h"
#include "RectangleObj.h"
#include <vector>
#include "TilePlay.h"

class BattleSceneUI;
class Button;
class Character;

class BattleScene : public Scene
{
protected:
	BattleSceneUI* ui;

	Dir currMoveDir;
	Evan* evan;
	Goblin00* goblin00;
	Dummy* dummy;
	VertexArrayObj* background;
	vector<vector<TilePlay*>> testTile;
	TilePlay* tilePlay;
	Vector2f nowTile;
	Vector2f nextTile;

	Vector2f screenCenterPos;
	Vector2u screenSize;
	bool b_centerPos;
	float gameScreenBottomLimit;
	float gameScreenTopLimit;

	vector<vector<RectangleObj*>*> battleGrid;
	bool BattleGrid;
	vector<Character*> prepare;
	Character* drag;
	Vector2f beforeDragPos;

public:
	BattleScene();
	virtual ~BattleScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	VertexArrayObj* GetBackground() { return background; }

	void CreateTestTile(int cols, int rows, float width, float height);

	void MoveTile(Dir currMoveDir);
	void ZoomIn();
	void ZoomOut();
	void AIMove();
};