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
class Panel : public SpriteObj
{
protected:

	SpriteObj m_resetButton;
	SpriteObj m_skillCount;
	SpriteObj m_resetCount;

	int m_skillCooldown;
	int m_resetCooldown;
	int m_skillCost;
	PanelTypes m_PanelTypes;



	RectangleObj m_BackGround;
	RectangleObj m_NameBackGround;
	RectangleObj m_InfoBackGround;

	TextObj m_SkillName;
	TextObj m_SkillInfo;

	wstring m_SkillNameStr;
	wstring m_SkillInfoStr;

	Vector2f m_NamePos;
	Vector2f m_InfoPos;

	bool isMouseOn;

public:
	Panel();
	~Panel();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter();


	bool CallResetButton(Vector2f pos);
	bool CallSkillButton(Vector2f pos);
	void ResetSkill();
	void SetSkillCooldown();
	string GetRandomSkill();
	void SetSkillBackGround();
	void SetSkillInfo();
	void SetWstring();
};

