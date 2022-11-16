#pragma once
#include "SpriteObj.h"
#include "ProgressBar.h"
#include "EnumClass.h"

class Character : public SpriteObj
{
protected:
	Character* target;

	ProgressBar* hpBar;
	Vector2f hpBarLocalPos;
	Vector2f destination;
	bool move;
	bool attack;
	int maxHp;
	int hp;
	int maxMp;
	int Mp;
	int dmg;

	AnimStates currState;

	float speed;

	Vector2f nowTile;
	Vector2f frontTile;
	Vector2f direction;
	Vector2f lastDirection;

	bool drawInBattle;
	// dev
	bool prepareUpdate;

public:
	Character();
	virtual ~Character();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState);
	AnimStates GetState() { return currState;  }

	void SetTarget(Character* target);
	void SetHpBarLocalPos(Vector2f pos);
	void SetMove(bool b) { move = b; }
	void SetDestination(Vector2f dest) { destination = dest; }


	void SetDrawInBattle(bool b) { drawInBattle = b; }
	bool GetDrawInBattle() { return drawInBattle; }
	// dev
	void SetCanUpdate(bool b) { prepareUpdate = b; }
	bool GetCanUpdate() { return prepareUpdate; }
};