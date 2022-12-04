#pragma once
#include "SpriteObj.h"

class Star : public SpriteObj
{
protected:
	int starNumber;

public:
	Star(int starNumber = 0);
	virtual ~Star();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetStarNumber(int num) { starNumber = num; }
	int& GetStarNumber() { return starNumber; }
	bool CalculateRandomChance();
	void UpdateTexture();
};