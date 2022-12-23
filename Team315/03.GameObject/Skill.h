#pragma once
#include "GameObj.h"
#include "Include.h"
#include <vector>

class Character;

class Skill : public GameObj
{
protected:
	vector<float> baseDamage;			// skill base damage
	vector<vector<Vector2i>> range;		// skill range
	int skillTier;						// starNumber
	vector<Vector2i> applyArea;

	Vector2f direction;
	Dir dir;

public:
	Skill(int starNumber);
	virtual ~Skill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Reset() override;
	virtual void Draw(RenderWindow& window) override;
	//virtual void SetRotation(Vector2f dir);
	void SetSkillDir(Vector2f dir);

	virtual void SetState(AnimStates newState);
	AnimStates GetState() { return currState; }
	float CalculatePotential(Character* character);
	virtual void SetSkillRange(Vector2f startPos);
	virtual void CastSkill(Character* caster);
	void SetSkillTier(int starNumber);

	Animator* GetAnimator() { return &animator; }
};