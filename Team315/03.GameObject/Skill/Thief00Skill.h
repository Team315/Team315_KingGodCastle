#pragma once
#include "Skill.h"

class Thief00Skill : public Skill
{
protected:
public:
	Thief00Skill(int starNumber);
	virtual ~Thief00Skill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void CastSkill(Character* caster) override;
};

