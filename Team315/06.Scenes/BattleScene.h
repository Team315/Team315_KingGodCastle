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

	// create character when summon (2x7) x(0, 6) y(16, 17)
	vector<Character*> prepareGrid;

	// set locate before battle (4x7) x(0, 6) y(10, 13)
	vector<vector<Character*>> battleGrid;
	Character* drag;
	Vector2f beforeDragPos;
	int battleCharacterCount;

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

	void MoveTile(Character* character, Dir currMoveDir);
	void ZoomIn();
	void ZoomOut();
	void AIMove();
	void DragAction(Character* character);
	int GetPrepareIdxFromCoord(Vector2i coord);
};

bool InPrepareGrid(Vector2i pos);
bool InBattleGrid(Vector2i pos);
int GetZeroElem(vector<Character*> vec);