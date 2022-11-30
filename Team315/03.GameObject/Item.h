#pragma once
#include "Character.h"

class Item : public GameObj
{
protected:

public:
	Item();
	virtual ~Item();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};