#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"

class GameObj : public SpriteObj
{
protected:
	Animator animator;
	AnimStates currState;
	
public:
	GameObj();
	virtual ~GameObj();

	virtual void Init() override;
	virtual void SetState(AnimStates newState);
	Animator GetSkillAnimator() { return animator; }
};