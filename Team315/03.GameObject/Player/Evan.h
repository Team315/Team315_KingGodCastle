#pragma once
#include "Include.h"
#include "Animator.h"
#include "Character.h"

class Evan : public Character
{
public:
	enum class States
	{
		None = -1,
		Idle,
		MoveToIdle,
		Move,
		Attack,
		Skill,
	};
protected:
	Animator animator;
	
	States currState;

	float speed;
	Vector2f direction;
	Vector2f lastDirection;
	Vector2f velocity;

	int playerMaxhp;
	int playerhp;
	int playerMaxMp;
	int playermp;
	int dmg;

public:
	Evan()
		: currState(States::None), speed(200.f), direction(1.f, 0.f), lastDirection(1.f, 0.f), velocity(0.f, -1000.f), playerMaxhp(1000), dmg(100), playerMaxMp(500)
	{
	}
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetState(States newState);

	void SetBackground(SpriteObj* bk);

	void UpdateInput();

	void OnCompleteAttack();
	void OnCompleteSkill();

	void UpdateIdle(float dt);
	void UpdateMoveToIdle(float dt);
	void UpdateMove(float dt);
	void UpdateAttack(float dt);
	void UpdateSkill(float dt);

	bool EqualFloat(float a, float b);
};

