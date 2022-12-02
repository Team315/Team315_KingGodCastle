#pragma once
#include "Skill.h"

class DanielSkill : public Skill
{
protected:
	vector<Animator*> skillEffect;
	vector<Sprite*> skillSprite;
public:
	DanielSkill();
	virtual ~DanielSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetState(AnimStates newState, GameObj* target, String t);

	virtual void CastSkill(Character* caster) override;
};