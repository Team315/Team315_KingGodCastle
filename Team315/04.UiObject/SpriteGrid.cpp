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

void SpriteGrid::SetSpriteScale(float x, float y)
{
	FloatRect fr = (FloatRect)sprite.getTextureRect();
	float width = x / fr.width;
	float height = y / fr.height;
	float min = width > height ? height : width;
	sprite.setScale(min, min);
}

void SpriteGrid::SetSpriteTexture(Texture& tex, bool resetRect)
{
	sprite.setTexture(tex, resetRect);
}