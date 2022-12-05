#pragma once
#include "Skill.h"

class Thief00Skill : public Skill
{
protected:
public:
	Thief00Skill(int starNumber);
	virtual ~Thief00Skill();

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
};