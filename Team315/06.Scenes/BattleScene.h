#pragma once
#include "Scene.h"
#include "Include.h"
#include <vector>

class BattleSceneUI;
class GameObj;
class RectangleObj;
class VertexArrayObj;

class BattleScene : public Scene
{
protected:
	BattleSceneUI* ui;

	Dir currMoveDir;

	Vector2f screenCenterPos;
	Vector2u screenSize;
	bool b_centerPos;
	float gameScreenBottomLimit;
	float gameScreenTopLimit;

	vector<vector<Tile*>>* curStage;
	int curChapIdx;
	int curStageIdx;

	bool playingBattle;

	// Create player character when summon (2x7) x(0, 6) y(16, 17)
	vector<GameObj*> prepareGrid;
	// draw rect only 2 x 7
	vector<RectangleObj*> prepareGridRect;

	// Set player character locate before battle (4x7) x(0, 6) y(10, 13)
	vector<GameObj*> battleGrid;

	GameObj* pick;
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

	void ZoomIn();
	void ZoomOut();
	void PickUpGameObj(GameObj* gameObj);
	void TranslateCoinState(float delta);
	void PutDownCharacter(vector<GameObj*>* start, vector<GameObj*>* dest,
		Vector2i startCoord, Vector2i destCoord);
	int GetIdxFromCoord(Vector2i coord);

	void SetCurrentStage(int chap, int stage);
};

bool InPrepareGrid(Vector2i pos);
bool InBattleGrid(Vector2i pos);
int GetZeroElem(vector<GameObj*>& vec);