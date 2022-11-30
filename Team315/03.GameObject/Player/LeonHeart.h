#pragma once
#include "Character.h"

class LeonHeart : public GameObj
{
protected:
public:
	LeonHeart(int starNumber = 0);
	virtual ~LeonHeart();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState) override;

	void OnCompleteAttack();
	void OnCompleteSkill();

	void UpdateIdle(float dt);
	void UpdateMoveToIdle(float dt);
	void UpdateMove(float dt);
	void UpdateAttack(float dt);
	void UpdateSkill(float dt);
};

