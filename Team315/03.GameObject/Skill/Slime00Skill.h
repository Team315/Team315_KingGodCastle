#pragma once
#include "Skill.h"

class Slime00Skill : public Skill
{
protected:

public:
	Slime00Skill(int starNumber);
	virtual ~Slime00Skill();

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
};