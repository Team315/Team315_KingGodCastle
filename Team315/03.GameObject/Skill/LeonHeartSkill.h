#pragma once
#include "Skill.h"

class LeonHeartSkill : public Skill
{
protected:
	vector<float> crowdControlTimer;
	Dir dir;

public:
	LeonHeartSkill(int starNumber);
	virtual ~LeonHeartSkill();

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
	void SetDir(Vector2f direction);
};