#pragma once
#include "GameObj.h"
#include "TwoFactorProgress.h"
#include "ProgressBar.h"
#include "Star.h"
#include <unordered_map>
#include "Map/FloodFill.h"
#include "Map/AStar.h"
#include "Bullet.h"
#include "Skill.h"

class Character : public GameObj
{
protected:
	Animator effectAnimator;
	Sprite effectSprite;
	unordered_map<StatType, Stat> stat;
	bool attackRangeType; // true square, false cross

	// UI
	TwoFactorProgress* hpBar;
	Star* star;

	Vector2f hpBarLocalPos;
	Vector2f starLocalPos;
	
	//Skill
	float ccTimer; // Crowd control timer
	float shieldAmount;
	float shieldAmountMin;
	bool noSkill;
	Skill* skill;

	Vector2f destination;
	bool move;
	bool attack;
	bool isAlive;

	float moveSpeed;
	Vector2f direction;
	Vector2f lastDirection;
	float m_attackDelay;

	GameObj* m_target;

	//FloodFill
	FloodFill m_floodFill;
	vector<Vector2i> m_GeneralArr;

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
	virtual void SetState(AnimStates newState) override;

	AnimStates GetState() { return currState; }

	void SetDestination(Vector2f dest)
	{
		move = true;
		destination = dest;
	}
	void SetHpBarValue(float val) { hpBar->SetProgressValue(val); }
	int GetStarNumber() { return star->GetStarNumber(); }
	Stat& GetStat(StatType statsEnum) { return stat[statsEnum]; }
	void SetStatsInit(json data);
	// attackType, true = ad / false = ap
	void TakeDamage(GameObj* attacker, bool attackType = true);
	// careType, true = heal / false = shield
	void TakeCare(GameObj* caster, bool careType = true);
	void AddShieldAmount(float amount) { shieldAmount += amount; }
	float GetShieldAmount() { return shieldAmount; }
	void UpgradeStar();
	void UpgradeCharacterSet();
	void UpgradeStats();
	void SetNoSkill(bool b) { noSkill = b; };
	bool GetNoSkill() { return noSkill; }
	void SetShieldMinValue(float value) { shieldAmountMin = value; }

	//battle
	void IsSetState(AnimStates newState);
	bool GetAttackRangeType() { return attackRangeType; };
	GameObj* GetTarget() { return m_target; };

	//FloodFill
	bool isAttack();

	//Astar
	bool PlayAstar();
	bool SetTargetDistance();
	void SetMainGrid(int r, int c, GameObj* character);
	void SetIsBattle(bool battleOnOff) { isBattle = battleOnOff; }
};