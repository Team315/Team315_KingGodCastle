#pragma once
#include "Scene.h"
#include "Include.h"
#include "TileBackground.h"
#include "PanelSkill/Panel.h"
class BattleSceneUI;
class GameObj;
class RectangleObj;
class VertexArrayObj;

class BattleScene : public Scene
{
protected:
	BattleSceneUI* ui;
	Sprite castleBackground;

	Vector2f screenCenterPos;
	Vector2u screenSize;
	bool b_centerPos;
	float gameScreenBottomLimit;
	float gameScreenTopLimit;

	vector<vector<Tile*>>* curStage;
	vector<TileBackground*> curBackGround; 
	vector<RectangleObj>* pickAttackRangeRect;
	vector<SpriteObj*> flags;

	// bool playingBattle;

	// Create player character when summon (2x7) x(0, 6) y(16, 17)
	vector<GameObj*> prepareGrid;
	// draw rect only 2 x 7
	vector<RectangleObj*> prepareGridRect;

	// Set player character locate before battle (4x7) x(0, 6) y(10, 13)
	vector<GameObj*> battleGrid;

	GameObj* pick;
	Vector2f beforeDragPos;

	float gameEndTimer;

	int remainLife;
	bool isGameOver;
	float gameOverTimer;

	bool stageEnd;
	bool stageResult;
	bool eventWindow;

	Panel m_panel;

public:
	BattleScene();
	virtual ~BattleScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void PutDownCharacter(vector<GameObj*>* start, vector<GameObj*>* dest,
		Vector2i startCoord, Vector2i destCoord);
	void PutDownItem(vector<GameObj*>* start, vector<GameObj*>* dest,
		Vector2i startCoord, Vector2i destCoord);

	void SetCurrentStage(int chap, int stage);
	void LoseFlag();
	void ZoomIn();
	void ZoomOut();
	void PickUpGameObj(GameObj* gameObj);
	void TranslateCoinState(float delta);
	int GetCurCharacterCount();
	void SetEventWindow(bool active) { eventWindow = active; }
};

int GetIdxFromCoord(Vector2i coord);
Vector2i GetCoordFromIdx(int idx, bool battle);
bool IsItem(GameObj* gameObj);
bool IsCharacter(GameObj* gameObj);
bool InPrepareGrid(Vector2i pos);
bool InBattleGrid(Vector2i pos);
int GetZeroElem(vector<GameObj*>& vec);