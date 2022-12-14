#pragma once
#include "Character.h"

class Daniel : public Character
{
protected:
	vector<Animator*> skillEffect;
	vector<Sprite*> skillSprite;

public:
	Daniel(bool mode = false, bool useExtraUpgrade = false, int starGrade = 0);
	virtual ~Daniel();

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