#include "Button.h"
#include "Include.h"

Button::Button()
	: btnTextLocalPos(0, 0), baseColor(Color::White), hoverColor(Color::Red)
{
}

Button::~Button()
{
}

void Button::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(btnText);
}

void Button::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	btnText.setPosition(position + btnTextLocalPos);
}

void Button::SetOrigin(Origins origin)
{
	SpriteObj::SetOrigin(origin);
	Utils::SetOrigin(btnText, origin);
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
	btnText.setFont(font);
	btnText.setString(textString);
	btnText.setFillColor(textColor);
	btnText.setCharacterSize(textSize);
	btnTextLocalPos = Vector2f(txtDeltaPosX, txtDeltaPosY);
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

void Button::SetTextStyle(Color textColor, int textSize, Color textOutlineColor, float textOutlineThickness)
{
	btnText.setFillColor(textColor);
	btnText.setCharacterSize(textSize);
	btnText.setOutlineColor(textOutlineColor);
	btnText.setOutlineThickness(textOutlineThickness);
}

void Button::SetButtonStyle(Color baseColor, Color hoverColor)
{
	this->baseColor = baseColor;
	this->hoverColor = hoverColor;
}

void Button::SetLocalPos(Vector2f pos)
{
	btnTextLocalPos = pos;
	SetPos(position);
}