#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"

class FireExplosion : public SpriteObj
{
protected:
	Animator m_FireExplosion;

	bool isPlaying;

public:
	FireExplosion();
	~FireExplosion();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetAni();

	void PlayingAni();
};

