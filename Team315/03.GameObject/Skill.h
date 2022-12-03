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

	Vector2i startPos;
	Vector2i destPos;
	int skillTier; // starNumber

public:
	Skill(int starNumber);
	virtual ~Skill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetRotation(Vector2f dir);

	virtual void SetState(AnimStates newState);
	AnimStates GetState() { return currState; }
	float CalculateDamage(Character* character);
	virtual void SetSkillRange(Vector2f startPos);
	virtual void CastSkill(Character* caster);
	void SetSkillTier(int starNumber);
};