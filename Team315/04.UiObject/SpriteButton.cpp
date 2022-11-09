#include "SpriteButton.h"

SpriteButton::SpriteButton()
	: buttonSpriteSpacing(0, 0)
{
}

SpriteButton::~SpriteButton()
{
}

void SpriteButton::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(buttonSprite);
	window.draw(buttonText);
}

void SpriteButton::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	buttonSprite.setPosition(pos + buttonSpriteSpacing);
	buttonText.setPosition(pos + buttonTextSpacing);
}

void SpriteButton::SetOrigin(Origins origin)
{
	Button::SetOrigin(origin);
	Utils::SetOrigin(buttonSprite, origin);
}

void SpriteButton::SetButton(Texture& backTexture,
	Font& font, wstring textString,
	Texture& buttonTexture,
	float txtDeltaPosX, float txtDeltaPosY, 
	float posX, float posY, float scaleX, float scaleY,
	Color baseColor, Color hoverColor,
	Color textColor, int textSize)
{
	Button::SetButton(backTexture, font, textString, txtDeltaPosX,
		txtDeltaPosY, posX, posY, scaleX, scaleY,
		baseColor, hoverColor, textColor, textSize);
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setScale(scaleX, scaleY);
}

void SpriteButton::SetButtonSize(float sizeX, float sizeY)
{
	buttonSprite.setScale(sizeX, sizeY);
}

void SpriteButton::SetButtonSpriteSpacing(float sizeX, float sizeY)
{
	buttonSpriteSpacing = { sizeX, sizeY };
}