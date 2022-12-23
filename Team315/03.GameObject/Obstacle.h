#pragma once
#include "SpriteObj.h"

class Obstacle : public SpriteObj
{
protected:

public:
	Obstacle(string path);
	virtual ~Obstacle();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};