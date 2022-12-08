#pragma once
#include "Character.h"

class Goblin04 : public Character
{
protected:
public:
	Goblin04(int skillTier = 0);
	virtual ~Goblin04();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};