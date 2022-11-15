#pragma once
#include "UIMgr.h"

class BattlePanel;
class VertexArrayObj;

class BattleSceneUI : public UIMgr
{
protected:
	BattlePanel* panel;

public:
	BattleSceneUI(Scene* scene);
	virtual ~BattleSceneUI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	BattlePanel* GetPanel() { return panel; }

	void CreateBackground(VertexArrayObj* vao, int rows, int cols, float quadWidth, float quadHeight);
};