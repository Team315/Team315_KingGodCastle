#pragma once
#include "Character.h"

class Thief01 : public Character
{
protected:
public:
	Thief01(int skillTier = 0);
	virtual ~Thief01();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};

