#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"

class DivineShield : public SpriteObj
{
protected:
	Animator m_DivineShield;

	bool isPlaying;

public:
	DivineShield();
	~DivineShield();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetAni();
	void SetIsPlaying(bool is);

	void PlayingAni();
};

