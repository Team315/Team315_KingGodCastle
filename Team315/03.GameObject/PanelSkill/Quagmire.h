#pragma once
#include "SpriteObj.h"
#include "Animator.h"

class Quagmire : public SpriteObj
{
protected:
	Animator m_Quagmire;

public:
	Quagmire();
	~Quagmire();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter();

};

