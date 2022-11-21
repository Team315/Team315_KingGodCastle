#pragma once
#include "Include.h"
#include "Animator.h"
#include "Character.h"
#include "TilePlay.h"

class Dummy : public Character
{
protected:
	Animator animator;

	float speed;

	//Vector2f velocity;

	bool isPlaying2;
public:
	Dummy() : speed(100.f), isPlaying2(false) {}
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState) override;

	void OnCompleteAttack();
	void OnCompleteSkill();

	void UpdateIdle(float dt);
	void UpdateMoveToIdle(float dt);
	void UpdateMove(float dt);
	void UpdateAttack(float dt);
};