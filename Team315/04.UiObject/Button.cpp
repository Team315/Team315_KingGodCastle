#include "Button.h"
#include "Include.h"

Button::Button()
	: baseColor(Color::White), hoverColor(Color::Red)
{
}

Button::~Button()
{
}

void Button::Draw(RenderWindow& window)
{
	BackgroundText::Draw(window);
}

void Button::SetPos(const Vector2f& pos)
{
	BackgroundText::SetPos(pos);
}

void Button::SetOrigin(Origins origin)
{
	BackgroundText::SetOrigin(origin);
}

void Button::SetButton(Texture& backTexture,
	Font& font, wstring textString,
	float txtDeltaPosX, float txtDeltaPosY, 
	float posX, float posY,
	float scaleX, float scaleY,
	Color baseColor, Color hoverColor,
	Color textColor, int textSize)
{
	sprite.setTexture(backTexture);
	sprite.setScale(scaleX, scaleY);
	text.setFont(font);
	text.setString(textString);
	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	textLocalPos = Vector2f(txtDeltaPosX, txtDeltaPosY);
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

void Button::SetButtonStyle(Color baseColor, Color hoverColor)
{
	this->baseColor = baseColor;
	this->hoverColor = hoverColor;
}