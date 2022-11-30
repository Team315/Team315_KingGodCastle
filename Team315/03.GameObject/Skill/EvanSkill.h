#pragma once
#include "Skill.h"

class EvanSkill : public Skill
{
protected:

public:
	EvanSkill();
	virtual ~EvanSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState);
};