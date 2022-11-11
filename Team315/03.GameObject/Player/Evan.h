#pragma once
#include "Include.h"
#include "Animator.h"
#include "Charactor.h"

class Goblin00;
class Evan : public Charactor
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
	SpriteObj* background;
	Goblin00* goblin00;

	int playerMaxhp;
	int playerhp;
	int playerMaxMp;
	int playermp;
	int dmg;
public:
	Evan() : currState(States::None), speed(200.f), direction(1.f, 0.f), lastDirection(1.f, 0.f), velocity(0.f, -1000.f), playerMaxhp(1000), dmg(100), playerMaxMp(500) {}
	void Init(Goblin00* goblin00);

	void SetState(States newState);

	void SetBackground(SpriteObj* bk);

	void UpdateInput();
	void Update(float dt);
	void Draw(RenderWindow& window);

	void OnCompleteAttack();
	void OnCompleteSkill();

	void UpdateIdle(float dt);
	void UpdateMoveToIdle(float dt);
	void UpdateMove(float dt);
	void UpdateAttack(float dt);
	void UpdateSkill(float dt);

	bool EqualFloat(float a, float b);
};

