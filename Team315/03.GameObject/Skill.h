#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"

class Skill : public SpriteObj
{
protected:
	Animator animator;
	Character* target;
	AnimStates currState;
public:
	Skill(int starNumber = 0);
	virtual ~Skill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState);
	AnimStates GetState() { return currState; }

	void SetTarget(Character* target);
};

