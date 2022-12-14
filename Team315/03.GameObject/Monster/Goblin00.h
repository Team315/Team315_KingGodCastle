#pragma once
#include "Character.h"

class Goblin00 : public Character
{
protected:
	vector<Animator*> skillEffect;
	vector<Sprite*> skillSprite;
public:
	Goblin00(bool mode = false, bool useExtraUpgrade = false, int starGrade = 0);
	virtual ~Goblin00();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};