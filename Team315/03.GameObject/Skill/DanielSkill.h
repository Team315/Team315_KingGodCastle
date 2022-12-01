#pragma once
#include "Skill.h"

class DanielSkill : public Skill
{
protected:
public:
	DanielSkill();
	virtual ~DanielSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};