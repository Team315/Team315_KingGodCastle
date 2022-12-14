#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"

class Quagmire : public SpriteObj
{
protected:
	Animator m_Quagmire;

	bool isPlaying;

public:
	Quagmire();
	~Quagmire();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetAni();


	void PlayingAni();
};

