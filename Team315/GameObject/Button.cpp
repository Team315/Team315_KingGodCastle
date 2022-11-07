#include "Button.h"
#include "../Frameworks.h"

Button::Button()
	: buttonTextDelta(0, 0), baseColor(Color::White), hoverColor(Color::Red)
{
}

Button::~Button()
{
}

void Button::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(buttonText);
}

void Button::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	buttonText.setPosition(pos + buttonTextDelta);
}

void Button::SetButton(Texture& texture,
	Font& font, string textString,
	float txtDeltaPosX, float txtDeltaPosY, 
	float posX, float posY,
	float scaleX, float scaleY,
	Color baseColor, Color hoverColor,
	Color textColor, int textSize)
{
	sprite.setTexture(texture);
	sprite.setScale(scaleX, scaleY);
	buttonText.setFont(font);
	buttonText.setString(textString);
	buttonText.setFillColor(textColor);
	buttonText.setCharacterSize(textSize);
	buttonTextDelta = Vector2f(txtDeltaPosX, txtDeltaPosY);
	SetPos(Vector2f(posX, posY));
	Vector2u textureSize = sprite.getTexture()->getSize();
	SetHitbox(FloatRect(0, 0, textureSize.x * scaleX, textureSize.y * scaleY), Origins::TL);
	this->baseColor = baseColor;
	this->hoverColor = hoverColor;
}

void Button::SetButtonSize(float sizeX, float sizeY)
{
	sprite.setScale(sizeX, sizeY);
}

bool Button::CollideTest(Vector2f pos)
{
	if (hitbox.getGlobalBounds().contains(pos))
	{
		return true;
	}
	return false;
}
