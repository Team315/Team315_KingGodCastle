#pragma once
#include "Skill.h"

class Character;

class EvanSkill : public Skill
{
protected:
	Dir dir;

public:
	EvanSkill(int skillTier);
	virtual ~EvanSkill();

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
	void SetDir(Vector2f direction);
};