#pragma once
#include "Character.h"

class Evan : public Character
{
protected:
	float skillSpeed;
	Vector2f skillDir;
public:
	Evan(bool mode = false, bool useExtraUpgrade = false, int starGrade = 0);
	virtual ~Evan();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	//void UpdateIdle(float dt);
	//void UpdateMoveToIdle(float dt);
	//void UpdateMove(float dt);
	//void UpdateAttack(float dt);
	//void UpdateSkill(float dt);
};