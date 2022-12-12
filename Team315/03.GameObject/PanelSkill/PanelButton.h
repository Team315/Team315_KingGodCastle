#pragma once
#include "SpriteObj.h"
#include "Include.h"

class PanelButton : public SpriteObj
{
protected:

	SpriteObj m_resetButton;
	SpriteObj m_skillCount;
	SpriteObj m_resetCount;

	int m_skillCooldown;
	int m_resetCooldown;

public:
	PanelButton();
	~PanelButton();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;


	bool CallResetButton(Vector2f pos);
	bool CallSkillButton(Vector2f pos);
	void ResetSkill();
	//virtual void Enter();
};

