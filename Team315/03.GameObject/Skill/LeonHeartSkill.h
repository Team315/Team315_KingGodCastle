#pragma once
#include "Skill.h"

class LeonHeartSkill : public Skill
{
protected:
	vector<float> crowdControlTimer;

public:
	LeonHeartSkill(int starNumber);
	virtual ~LeonHeartSkill();

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
};