#pragma once
#include "Include.h"
#include "Animator.h"
#include "Character.h"

class Goblin00 : public Character
{
protected:
	Animator animator;

	float dist;
	float speed;
	Vector2f dest;
	Vector2f direction;
	Vector2f lastDirection;
	Vector2f velocity;

	bool isPlaying2;
public:
	Goblin00()
		: speed(200.f), direction(0.f, 0.f), lastDirection(0.f, 0.f), velocity(0.f, -1000.f), isPlaying2(false)
	{
	}
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

	void StopTranslate();
};

