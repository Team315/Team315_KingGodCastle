#pragma once
#include "Character.h"

class Slime00 : public GameObj
{
protected:
public:
	Slime00(int starNumber = 0);
	virtual ~Slime00();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState) override;

	void OnCompleteSkill();

	void UpdateIdle(float dt);
	void UpdateSkill(float dt);
};

