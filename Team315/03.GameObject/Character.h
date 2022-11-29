#pragma once
#include "SpriteObj.h"
#include "Animator.h"
#include "TwoFactorProgress.h"
#include "Star.h"
#include "Include.h"
#include <unordered_map>
#include "Map/FloodFill.h"
#include "Map/AStar.h"
#include "Bullet.h"

class Character : public SpriteObj
{
protected:
	Animator animator;
	Animator attackEffect;
	Character* target;
	unordered_map<Stats, Stat> stat;
	bool attackRangeType; // true square, false cross

	// UI
	//ProgressBar* hpBar;
	TwoFactorProgress* hpBar;
	Star* star;
	
	Vector2f hpBarLocalPos;
	Vector2f starLocalPos;
	//
	float ccTimer; // Crowd control timer
	float shieldAmount;
	bool noSkill;

	Vector2f destination;
	bool move;
	bool attack;
	bool isAlive;

	AnimStates currState;

	float moveSpeed;
	Vector2f direction;
	Vector2f lastDirection;

	bool drawingOnBattle;

	float m_attackDelay;
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
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void Fire();

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
	void TakeDamage(Character* attacker, bool attackType = true); // true = ad / false = ap
	void UpgradeStar();
	void UpgradeCharacterSet();
	void SetNoSkill(bool b) { noSkill = b; };
	bool GetNoSkill() { return noSkill; }

	//battle
	void IsSetState(AnimStates newState);
	// Dev
	void PrintStats();

	//FloodFill
	unordered_map<Stats, Stat>& GetStat();
	bool isAttack();

	//Astar
	void PlayAstar();
	void SetTargetDistance();
	void SetMainGrid(int r, int c, Character* character);
	void SetIsBattle(bool battleOnOff) { isBattle = battleOnOff; }
};