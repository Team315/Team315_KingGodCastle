#pragma once
#include "SpriteObj.h"
#include "TextObj.h"
#include "Include.h"
#include "Animator.h"

class Brazier : public SpriteObj
{
protected:
	int m_grade;
	int m_maxGrade;
	Sprite m_sFlame;
	Animator m_Flame;

	SpriteObj m_maxLevelSprite;
	SpriteObj m_collectSprite;
	TextObj m_levelNumber;
	
public:
	Brazier(int max, int grade);
	virtual ~Brazier();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void Enter();

	bool ClickButton(Vector2f nowMousePos);
	void PlayAni(int grade);

	int GetGrade() { return m_grade; };
};