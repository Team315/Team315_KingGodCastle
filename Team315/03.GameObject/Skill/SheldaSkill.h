#pragma once
#include "Skill.h"

class SheldaSkill : public Skill
{
protected:

public:
	SheldaSkill(int starNumber);
	virtual ~SheldaSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};
