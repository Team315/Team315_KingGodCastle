#pragma once
#include "Character.h"

class Slime03 : public Character
{
protected:
public:
	Slime03(bool mode = false, bool fixedStar = false, int skillTier = 0);
	virtual ~Slime03();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};

