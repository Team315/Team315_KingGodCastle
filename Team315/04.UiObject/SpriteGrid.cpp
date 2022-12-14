#include "SpriteGrid.h"

SpriteGrid::SpriteGrid(float x, float y)
	: RectangleObj(x, y)
{
}

SpriteGrid::~SpriteGrid()
{
}

void SpriteGrid::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
	window.draw(sprite);
}

void SpriteGrid::SetOrigin(Origins origin)
{
	RectangleObj::SetOrigin(origin);
	Utils::SetOrigin(sprite, origin);
}

void SpriteGrid::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	sprite.setPosition(pos);
}

void SpriteGrid::SetScale(float x, float y)
{
	shape.setScale(x, y);
	sprite.setScale(x, y);
}

void SpriteGrid::SetSpriteScale(float x, float y)
{
	float min = Utils::GetMinScaleRatioFromFloatRect(
		x, y, (FloatRect)sprite.getTextureRect());
	sprite.setScale(min, min);
}

void SpriteGrid::SetSpriteTexture(Texture& tex, bool resetRect)
{
	sprite.setTexture(tex, resetRect);
}