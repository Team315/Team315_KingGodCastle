#pragma once
#include "UIMgr.h"

class BattlePanel;
class VertexArrayObj;
class RectangleObj;
class StatPopupWindow;

class BattleSceneUI : public UIMgr
{
protected:
	BattlePanel* panel;
	StatPopupWindow* statPopup;

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
	void CreateBackground(VertexArrayObj* vao, int rows, int cols, float quadWidth, float quadHeight);

	void SetStatPopup(bool active, Vector2f viewCenter, Vector2f pos = { 0, 0 });
};