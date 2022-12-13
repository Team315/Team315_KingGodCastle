#pragma once
#include "SpriteObj.h"
#include "Include.h"

enum class PanelTypes
{
	None = 0,
	ManaBless,
	Meteor,
	PingerSnap,
	Quagmire,
	Shield,
};
class PanelButton : public SpriteObj
{
protected:

	SpriteObj m_resetButton;
	SpriteObj m_skillCount;
	SpriteObj m_resetCount;

	int m_skillCooldown;
	int m_resetCooldown;

	PanelTypes m_PanelTypes;
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
	string GetRandomSkill();
	//virtual void Enter();
};

