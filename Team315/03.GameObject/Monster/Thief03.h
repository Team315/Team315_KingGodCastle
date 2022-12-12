#pragma once
#include "Character.h"

class Thief03 : public Character
{
protected:
public:
	Thief03(bool mode = false, bool useExtraUpgrade = false, int skillTier = 0);
	virtual ~Thief03();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};

