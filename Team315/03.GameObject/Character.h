#pragma once
#include "SpriteObj.h"

class Character : public SpriteObj
{
protected:
	Character* target;

public:
	Character();
	virtual ~Character();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTarget(Character* target);
};