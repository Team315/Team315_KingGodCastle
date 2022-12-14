#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"
#include "GameObj.h"

class Quagmire : public GameObj
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
	void SetIsPlaying(bool is);

	void PlayingAni();
	void ActionSkill();
};

