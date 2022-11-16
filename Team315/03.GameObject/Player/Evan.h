#pragma once
#include "Include.h"
#include "Animator.h"
#include "Character.h"
#include "../05.ToolObject/TilePlay.h"

class Evan : public Character
{

protected:
	Animator animator;

	float speed;
	Vector2f direction;
	Vector2f lastDirection;
	Vector2f velocity;
	
	vector<vector<RectangleObj*>*> overlay;
	vector<vector<TilePlay*>> testTile;
	Vector2f nowTile;
public:
	Evan()
		: speed(300.f), direction(1.f, 0.f), lastDirection(1.f, 0.f), velocity(0.f, -1000.f)
	{
	}
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState) override;

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

