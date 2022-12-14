#pragma once
#include "SpriteObj.h"
#include "rapidcsv.h"
#include "Include.h"

enum class PanelTypes
{
	BlessOfMana,
	FireExplosion,
	FingerSnap,
	Quagmire,
	DivineShield,
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

	string m_SkillNameStr;
	string m_SkillInfoStr;

	Vector2f m_NamePos;
	Vector2f m_InfoPos;

	bool isMouseOn;

	bool isPlaying;
	bool isCurrPlaying;


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
	bool CallSkillPlayButton(Vector2f pos);

	void ResetSkill();
	void SetSkillButtonPos();
	void SetSkillCooldown();
	string GetRandomSkill();
	void SetSkillBackGround();
	void SetSkillInfo();
	void SetDataTable();
	void SetIsPlay(bool isplay);
};

