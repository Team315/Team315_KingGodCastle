#pragma once
#include "Skill.h"

class Goblin00Skill : public Skill
{
protected:
	vector<float> crowdControlTimer;

public:
	Goblin00Skill(int starNumber);
	virtual ~Goblin00Skill();

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
};