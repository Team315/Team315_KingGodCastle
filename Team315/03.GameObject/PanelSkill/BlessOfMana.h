#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"

class BlessOfMana : public SpriteObj
{
	Animator m_BlessOfMana;

	bool isPlaying;

public:
	BlessOfMana();
	~BlessOfMana();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetAni();


	void PlayingAni();
};

