#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"
#include "GameObj.h"

class DivineShield : public GameObj
{
protected:
	Animator m_DivineShield;

	float m_time;
	float m_Settime;
	bool isPlaying;

public:
	DivineShield();
	~DivineShield();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTime();
	void SetAni();
	void SetIsPlaying(bool is);

	void PlayingAni();
	void ActionSkill();
	void EndSkill();
};

