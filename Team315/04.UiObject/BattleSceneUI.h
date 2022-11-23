#pragma once
#include "UIMgr.h"

class BattlePanel;
class VertexArrayObj;
class RectangleObj;

class BattleSceneUI : public UIMgr
{
protected:
	BattlePanel* panel;
	vector<RectangleObj*> prepareGrid;
	RectangleObj* statPopup;

public:
	BattleSceneUI(Scene* scene);
	virtual ~BattleSceneUI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetOrigin(Origins origin) override;

	BattlePanel* GetPanel() { return panel; }
	Vector2f GetGridPos(int idx);
	void CreateBackground(VertexArrayObj* vao, int rows, int cols, float quadWidth, float quadHeight);

	// draw rect only 4 x 7
	vector<vector<RectangleObj*>> battleGridRect;
	bool b_battleGridRect;
};