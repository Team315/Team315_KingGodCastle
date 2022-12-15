#pragma once
#include "GameObj.h"
#include "TwoFactorProgress.h"
#include "ProgressBar.h"
#include "Star.h"
#include <unordered_map>
#include "Map/FloodFill.h"
#include "Map/AStar.h"
#include "SpriteGrid.h"

class Item;
class Skill;

class Character : public GameObj
{
protected:
	Animator effectAnimator;
	Sprite effectSprite;
	Animator crowdControlAnimator;
	Sprite crowdControlSprite;
	unordered_map<StatType, Stat> stat;
	bool attackRangeType; // true square, false cross
	vector<Item*> items;
	vector<SpriteGrid*> itemGrid;
	bool hit;
	float hitDelta;
	Sprite shadow;

	//Resource
	unordered_map<ResStringType, string> resStringTypes;
	unordered_map<Dir, Vector2f> attackPos;
	unordered_map<Dir, Vector2f> skillPos;
	Dir dirType;

	// UI
	TwoFactorProgress* hpBar;
	ProgressBar* mpBar;
	Star* star;

	Vector2f hpBarLocalPos;
	Vector2f starLocalPos;
	
	//Skill
	float ccTimer; // Crowd control timer
	float shieldAmount;
	float shieldAmountMin;
	float initManaPoint;
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
	vector<RectangleObj*> m_attackAreas;

	//Astar
	AStar m_aStar;
	EnemyInfo enemyInfo;
	string targetType;
	bool isBattle;
	float astarDelay;

public:
	// mode false - summon, true - combine
	Character(bool mode = false, bool useExtraUpgrade = false, int starNumber = 0);
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
	int GetStarNumber() { return star->GetStarNumber(); }
	Stat& GetStat(StatType statsEnum) { return stat[statsEnum]; }
	void SetStatsInit(json data);
	void TakeDamage(GameObj* attacker, AttackTypes attackType = AttackTypes::Normal);
	// careType, true = heal / false = shield
	void TakeCare(GameObj* caster, bool careType = true);
	void TakeCare(float amount, bool careType = true);
	// buffType, true = buff / false = debuff
	void TakeBuff(StatType sType, float potential, bool mode = true, Character* caster = nullptr);
	void AddShieldAmount(float amount) { shieldAmount += amount; }
	float GetShieldAmount() { return shieldAmount; }
	void UpgradeStar(bool mode = false, bool useExtraUpgrade = false);
	void UpgradeCharacterSet();
	void UpgradeStats();
	bool SetItem(Item* newItem);
	void PutItem(Item* putItem);
	void UpdateItems();
	void UpdateItemDelta(StatType sType, float value);
	vector<Item*>& GetItems() { return items; }
	void SetCrowdControl(float time);

	//battle
	void IsSetState(AnimStates newState);
	GameObj* GetTarget() { return m_target; };
	Skill* GetSkill() { return skill; }

	//FloodFill
	bool isAttack();
	void OnOffAttackAreas(bool onOff);
	vector<RectangleObj>* GetAreas() { return m_floodFill.GetAreas(); }

	//Astar
	bool SetTargetDistance();
	void SetMainGrid(int r, int c, GameObj* character);
	void SetIsBattle(bool battleOnOff) { isBattle = battleOnOff; }

	//State
	void AnimationInit();
	void IdleAnimation();
	void MoveToIdleAnimation();
	void MoveAnimation();
	void AttackAnimation(Vector2f attackPos);
	void SkillAnimation(Vector2f skillPos);

	void OnCompleteAttack();
	void OnCompleteSkill();

	void UpdateIdle(float dt);
	void UpdateMoveToIdle(float dt);
	void UpdateMove(float dt);
	void UpdateAttack(float dt);
	void UpdateSkill(float dt);

	void SetDir(Vector2f direction);
	bool GetNoSkill() { return noSkill; }
	void UpdateHpbar();
	void UpdateMpbar();
	void SetInitManaPoint(float value);
};