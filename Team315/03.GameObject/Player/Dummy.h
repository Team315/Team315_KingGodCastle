#pragma once
#include "Include.h"
#include "Animator.h"
#include "Character.h"
#include "TilePlay.h"

class Dummy : public Character
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

	float dist;
	float speed;
	Vector2i beforeTile;
	Vector2i currTile;

	Vector2f dest;
	Vector2f direction;
	Vector2f lastDirection;
	Vector2f velocity;

	vector<vector<TilePlay*>> moveTile;
	bool isPlaying2;
public:
	Dummy() : currState(States::None), speed(200.f), direction(0.f, 0.f), lastDirection(0.f, 0.f), velocity(0.f, -1000.f), isPlaying2(false), currTile({-1,-1}), beforeTile({-1,-1}) {}
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	void SetTilePos(const Vector2i& tpos);
	const Vector2i& GetTilePos() const;

	void SetDest(Vector2f dest);
	Vector2f GetDest();

	void SetState(States newState);

	void OnCompleteAttack();
	void OnCompleteSkill();

	void UpdateIdle(float dt);
	void UpdateMoveToIdle(float dt);
	void UpdateMove(float dt);
	void UpdateAttack(float dt);

	bool EqualFloat(float a, float b);

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	void StopTranslate();
};

