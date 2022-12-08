#pragma once
#include "Character.h"

class Thief00 : public Character
{
protected:
public:
	Thief00(bool mode = false, bool fixedStar = false, int skillTier = 0);
	virtual ~Thief00();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};