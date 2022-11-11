#include "SpriteButton.h"

SpriteButton::SpriteButton()
	: btnSpriteLocalPos(0, 0)
{
}

SpriteButton::~SpriteButton()
{
}

void SpriteButton::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(btnSprite);
	window.draw(btnText);
}

void SpriteButton::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	btnSprite.setPosition(pos + btnSpriteLocalPos);
	btnText.setPosition(pos + btnTextLocalPos);
}

void SpriteButton::SetOrigin(Origins origin)
{
	Button::SetOrigin(origin);
	Utils::SetOrigin(btnSprite, origin);
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
	btnSprite.setTexture(buttonTexture);
	btnSprite.setScale(scaleX, scaleY);
}

void SpriteButton::SetButtonSize(float sizeX, float sizeY)
{
	btnSprite.setScale(sizeX, sizeY);
}

void SpriteButton::SetBtnSpriteLocalPos(float sizeX, float sizeY)
{
	btnSpriteLocalPos = { sizeX, sizeY };
}

void SpriteButton::SetButtonTextColor(Color textColor, Color outlineColor, float OutlineThickness)
{
	btnText.setFillColor(textColor);
	btnText.setOutlineColor(outlineColor);
	btnText.setOutlineThickness(OutlineThickness);
}