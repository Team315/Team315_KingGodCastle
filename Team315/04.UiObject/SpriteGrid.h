#pragma once
#include "RectangleObj.h"

class SpriteGrid : public RectangleObj
{
protected:
	Sprite sprite;

public:
	SpriteGrid(float x = 0, float y = 0);
	virtual ~SpriteGrid();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetOrigin(Origins origin) override;
	virtual void SetPos(const Vector2f& pos) override;
	
	void SetSpriteScale(float x, float y);
	void SetSpriteTexture(Texture& tex);
};