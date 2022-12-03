#pragma once
#include "Skill.h"

class Character;

class EvanSkill : public Skill
{
protected:
public:
	EvanSkill(int skillTier);
	virtual ~EvanSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetRotation(Vector2f dir);
	virtual void CastSkill(Character* caster) override;
};