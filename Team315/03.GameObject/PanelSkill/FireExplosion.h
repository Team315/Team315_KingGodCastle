#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"
#include "GameObj.h"

class FireExplosion : public GameObj
{
protected:
	Animator m_FireExplosion;

	int m_damege;
	bool isPlaying;

public:
	FireExplosion();
	~FireExplosion();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetDamege();
	void SetAni();
	void SetIsPlaying(bool is);
	void PlayingAni();
	void ActionSkill();
};

