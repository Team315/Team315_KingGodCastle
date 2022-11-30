#pragma once
#include "GameObj.h"
#include "TwoFactorProgress.h"
#include "ProgressBar.h"
#include "Star.h"
#include <unordered_map>
#include "Map/FloodFill.h"
#include "Map/AStar.h"
#include "Bullet.h"

class Character : public GameObj
{
protected:
	Animator attackEffect;
	Sprite attackSprite;
	unordered_map<Stats, Stat> stat;
	bool attackRangeType; // true square, false cross

	// UI
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


	float moveSpeed;
	Vector2f direction;
	Vector2f lastDirection;

	float m_attackDelay;
	//FloodFill
	FloodFill m_floodFill;

	//Astar
	AStar m_aStar;
	EnemyInfo enemyInfo;
	string targetType;
	bool isBattle;
	float astarDelay;

public:
	Character(int starNumber = 0);
	virtual ~Character();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetState(AnimStates newState);

	AnimStates GetState() { return currState; }

	void SetDestination(Vector2f dest)
	{
		move = true;
		destination = dest;
	}
	void SetHpBarValue(float val) { hpBar->SetProgressValue(val); }
	int GetStarNumber() { return star->GetStarNumber(); }
	Stat& GetStat(Stats statsEnum) { return stat[statsEnum]; }
	void SetStatsInit(json data);
	// attackType, true = ad / false = ap
	void TakeDamage(GameObj* attacker, bool attackType = true);
	// careType, true = heal / false = shield
	void TakeCare(GameObj* caster, bool careType = true);
	void AddShieldAmount(float amount) { shieldAmount += amount; }
	float GetShieldAmount() { return shieldAmount; }
	void UpgradeStar();
	void UpgradeCharacterSet();
	void SetNoSkill(bool b) { noSkill = b; };
	bool GetNoSkill() { return noSkill; }

	//battle
	void IsSetState(AnimStates newState);
	// Dev
	// void PrintStats();

	//FloodFill
	unordered_map<Stats, Stat>& GetStat();
	bool isAttack();

	//Astar
	void PlayAstar();
	bool SetTargetDistance();
	void SetMainGrid(int r, int c, GameObj* character);
	void SetIsBattle(bool battleOnOff) { isBattle = battleOnOff; }
};