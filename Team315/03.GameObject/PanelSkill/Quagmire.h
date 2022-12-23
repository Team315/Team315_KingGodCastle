#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"
#include "SpriteObj.h"

class Quagmire : public SpriteObj
{
protected:
	Animator m_Quagmire;

	float m_time;
	float m_attackSpeed;
	
	bool isPlaying;

public:
	Quagmire();
	~Quagmire();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetAttackSpeed();
	void SetAni();
	void SetIsPlaying(bool is);

	void PlayingAni();
	void ActionSkill();
	void EndSkill();
};

