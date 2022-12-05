#pragma once
#include "Skill.h"

class ArveronSkill : public Skill
{
protected:
	vector<float> crowdControlTimer;

public:
	ArveronSkill(int starNumber);
	virtual ~ArveronSkill();

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
};