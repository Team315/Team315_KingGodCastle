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
	vector<Vector2f> prepareGridPos;

public:
	BattleSceneUI(Scene* scene);
	virtual ~BattleSceneUI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	BattlePanel* GetPanel() { return panel; }
	Vector2f GetPrepareGridPos(int idx) { return prepareGridPos[idx]; }

	void CreateBackground(VertexArrayObj* vao, int rows, int cols, float quadWidth, float quadHeight);
};