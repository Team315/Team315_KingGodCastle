#pragma once
#include "Character.h"

class Slime00 : public Character
{
protected:
	float mpTimer;
	float duration;

public:
	Slime00(int skillTier = 0);
	virtual ~Slime00();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState) override;

	void OnCompleteSkill();

	void UpdateIdle(float dt);
	void UpdateSkill(float dt);
};