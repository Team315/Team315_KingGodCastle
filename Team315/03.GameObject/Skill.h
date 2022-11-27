#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "Include.h"
#include <list>

class Character;

class Skill : public SpriteObj
{
protected:
	Animator animator;
	Character* target;
	AnimStates currState;
	float damage;
	Vector2i startPos;
	Vector2i destPos;
	list<Vector2i> area;

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