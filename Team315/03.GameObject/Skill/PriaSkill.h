#pragma once
#include "Skill.h"

class PriaSkill : public Skill
{
protected:
	vector<float> crowdControlTimer;

public:
	PriaSkill(int starNumber);
	virtual ~PriaSkill();

	/*virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;*/

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
};