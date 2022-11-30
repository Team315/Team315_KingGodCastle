#pragma once
#include "GameObj.h"

class Obstacle : public GameObj
{
protected:

public:
	Obstacle(string path);
	virtual ~Obstacle();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};