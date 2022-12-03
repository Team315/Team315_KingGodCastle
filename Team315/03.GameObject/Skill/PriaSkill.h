#pragma once
#include "Skill.h"

class PriaSkill : public Skill
{
protected:
public:
	PriaSkill(int starNumber);
	virtual ~PriaSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};