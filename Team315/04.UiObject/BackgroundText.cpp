#include "BackgroundText.h"

BackgroundText::BackgroundText()
	: textLocalPos(0, 0)
{
}

BackgroundText::~BackgroundText()
{
}

void BackgroundText::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(text);
}

void BackgroundText::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	text.setPosition(position + textLocalPos);
}

void BackgroundText::SetOrigin(Origins origin)
{
	SpriteObj::SetOrigin(origin);
	Utils::SetOrigin(text, origin);
}

void BackgroundText::SetTextLocalPos(Vector2f localPos)
{
	textLocalPos = localPos;
	SetPos(position);
}

void BackgroundText::SetTextStyle(Color textColor, int textSize, Color textOutlineColor, float textOutlineThickness)
{
	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	text.setOutlineColor(textOutlineColor);
	text.setOutlineThickness(textOutlineThickness);
}