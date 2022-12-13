#include "SpriteObj.h"

SpriteObj::SpriteObj()
{
}

SpriteObj::~SpriteObj()
{
}

void SpriteObj::Draw(RenderWindow& window)
{
    window.draw(sprite);
	Object::Draw(window);
}

void SpriteObj::SetTexture(Texture& tex, bool resetRect)
{
    sprite.setTexture(tex, resetRect);
}

void SpriteObj::SetOrigin(Origins origin)
{
    Utils::SetOrigin(sprite, origin);
}

void SpriteObj::SetScale(float x, float y)
{
	sprite.setScale(x, y);
	SetHitboxScale(x, y);
}

void SpriteObj::SetColor(Color color)
{
	sprite.setColor(color);
}

void SpriteObj::SetAlhpa(int num)
{
	Color color = sprite.getColor();
	color.a = num;
	SetColor(color);
}

void SpriteObj::SetTextureRect(const IntRect& rect)
{
	sprite.setTextureRect(rect);
}

const IntRect& SpriteObj::GetTextureRect() const
{
	return sprite.getTextureRect();
}

Vector2f SpriteObj::GetSize() const
{
	FloatRect rect = sprite.getLocalBounds();

	return Vector2f(rect.width, rect.height);
}

FloatRect SpriteObj::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

Color SpriteObj::GetColor() const
{
	return sprite.getColor();
}

void SpriteObj::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(position);
}