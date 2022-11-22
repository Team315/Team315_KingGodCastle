#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "ProgressBar.h"
#include "Star.h"
#include "EnumClass.h"
#include "Struct.h"
#include <map>

class Character : public SpriteObj
{
protected:
	Animator animator;
	Character* target;
	map<Stats, Stat*> stat;
	
	// UI
	ProgressBar* hpBar;
	Star* star;
	
	Vector2f hpBarLocalPos;
	Vector2f starLocalPos;
	//

	Vector2f destination;
	bool move;
	bool attack;
	bool isAlive;

	int maxHp;
	int hp;
	int maxMp;
	int Mp;
	int Ad;
	int Ap;

	AnimStates currState;

	float moveSpeed;

	Vector2f nowTile;
	Vector2f frontTile;
	Vector2f direction;
	Vector2f lastDirection;

	bool drawingOnBattle;

public:
	Character(int starNumber = 0);
	virtual ~Character();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState);
	AnimStates GetState() { return currState;  }

	void SetTarget(Character* target);
	void SetMove(bool b) { move = b; }
	void SetDestination(Vector2f dest) { destination = dest; }

	void SetDrawingOnBattle(bool b) { drawingOnBattle = b; }
	bool GetDrawingOnBattle() { return drawingOnBattle; }

	void SetHpBarValue(float val) { hpBar->SetProgressValue(val); }
	int GetStarNumber() { return star->GetStarNumber(); }
	Stat& GetStat(Stats statsEnum) { return *stat[statsEnum]; }
	void TakeDamage(float damage);
	void UpgradeStar();
	void UpgradeCharacterSet();
};