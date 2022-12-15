#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"

class BlessOfMana : public SpriteObj
{
	Animator m_BlessOfMana;

	int m_count;
	float m_addMana;
	float m_time;
	bool isPlaying;

public:
	BlessOfMana();
	~BlessOfMana();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetMana();
	void SetAni();
	void SetIsPlaying(bool is);

	void PlayingAni();
	void ActionSkill();
	void EndSkill();
};

