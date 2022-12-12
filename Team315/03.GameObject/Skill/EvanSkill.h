#pragma once
#include "Skill.h"
#include "Bullet.h"

class Character;

class EvanSkill : public Skill
{
protected:
	vector<Sprite*> evanSkill;
public:
	EvanSkill(int skillTier);
	virtual ~EvanSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetSkillRange(Vector2f startPos) override;
	virtual void CastSkill(Character* caster) override;
	void SetDir(Vector2f direction);
};