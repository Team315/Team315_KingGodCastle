#pragma once
#include "Character.h"

class Obstacle : public Character
{
protected:

public:
	Obstacle(string path);
	virtual ~Obstacle();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};