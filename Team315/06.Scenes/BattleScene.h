#pragma once
#include "Scene.h"
#include "Include.h"
#include <vector>
#include "Map/AStar.h"

class BattleSceneUI;
class Button;
class Character;
class RectangleObj;
class VertexArrayObj;

class BattleScene : public Scene
{
protected:
	BattleSceneUI* ui;
	Character* test;

	Dir currMoveDir;
	VertexArrayObj* background;

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
	vector<Character*> prepareGrid;
	// draw rect only 2 x 7
	vector<RectangleObj*> prepareGridRect;

	// Set player character locate before battle (4x7) x(0, 6) y(10, 13)
	vector<Character*> battleGrid;

	// Set monster character locate before battle with data imported from GameManager
	// When the game starts, the characters on the battleGrid are also taken.
	vector<Character*> mainGrid;
	Character* pick;
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

	VertexArrayObj* GetBackground();

	void MoveTile(Character* character, Dir currMoveDir);
	void ZoomIn();
	void ZoomOut();
	void AIMove();
	void PickUpCharacter(Character* character);
	void PutDownCharacter(vector<Character*>* start, vector<Character*>* dest,
		Vector2i startCoord, Vector2i destCoord);
	int GetIdxFromCoord(Vector2i coord);

	void SetCurrentStage(int chap, int stage);
	Character* GetMainGridCharacter(int r, int c);
	void SetMainGrid(int r, int c, Character* character);
};

bool InPrepareGrid(Vector2i pos);
bool InBattleGrid(Vector2i pos);
int GetZeroElem(vector<Character*>& vec);