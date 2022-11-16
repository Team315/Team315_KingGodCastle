#pragma once
#include "Include.h"
#include "Animator.h"
#include "Character.h"

class Goblin00 : public Character
{
protected:
	Animator animator;

	float speed;

	bool isPlaying2;
public:
	Goblin00();
	virtual ~Goblin00();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState) override;
	
	void OnCompleteAttack();

	void UpdateIdle(float dt);
	void UpdateMoveToIdle(float dt);
	void UpdateMove(float dt);
	void UpdateAttack(float dt);

	bool EqualFloat(float a, float b);
};

