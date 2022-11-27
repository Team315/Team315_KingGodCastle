#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "ProgressBar.h"
#include "Star.h"
#include "Include.h"
#include <unordered_map>
#include "Map/FloodFill.h"
#include "Map/AStar.h"

class Character : public SpriteObj
{
protected:
	Animator animator;
	Character* target;
	unordered_map<Stats, Stat> stat;
	bool attackRangeType; // true square, false cross

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

	AnimStates currState;

	float moveSpeed;
	Vector2f direction;
	Vector2f lastDirection;

	bool drawingOnBattle;

	//FloodFill
	FloodFill m_floodFill;

	//Astar
	AStar m_aStar;
	EnemyInfo enemyInfo;
	string targetType;
	bool isBattle;

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
	void SetDestination(Vector2f dest)
	{
		move = true;
		destination = dest;
	}

	void SetDrawingOnBattle(bool b) { drawingOnBattle = b; }
	bool GetDrawingOnBattle() { return drawingOnBattle; }

	void SetHpBarValue(float val) { hpBar->SetProgressValue(val); }
	int GetStarNumber() { return star->GetStarNumber(); }
	Stat& GetStat(Stats statsEnum) { return stat[statsEnum]; }
	void SetStatsInit(json data);
	void TakeDamage(float damage);
	void UpgradeStar();
	void UpgradeCharacterSet();
	void PrintStats();

	//FloodFill
	unordered_map<Stats, Stat> GetStat();
	bool isAttack();

	//Astar
	void PlayAstar();
	void SetTargetDistance();
	void SetMainGrid(int r, int c, Character* character);
	void SetIsBattle(bool battleOnOff) { isBattle = battleOnOff; }
	
};