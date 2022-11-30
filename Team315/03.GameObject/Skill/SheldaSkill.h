#pragma once
#include "Skill.h"

class SheldaSkill : public Skill
{
protected:

public:
	SheldaSkill();
	virtual ~SheldaSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};
