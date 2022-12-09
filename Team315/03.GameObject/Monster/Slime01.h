#pragma once
#include "Character.h"

class Slime01 : public Character
{
protected:
public:
	Slime01(bool mode = false, bool useExtraUpgrade = false, int skillTier = 0);
	virtual ~Slime01();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};

