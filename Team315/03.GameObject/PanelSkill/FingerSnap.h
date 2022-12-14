#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"

class FingerSnap : public SpriteObj
{
protected:
	Animator m_FingerSnap;

	bool isPlaying;

public:
	FingerSnap();
	~FingerSnap();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetAni();


	void PlayingAni();
};

