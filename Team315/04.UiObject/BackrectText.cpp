#include "BackrectText.h"

BackrectText::BackrectText(float x, float y)
	: RectangleObj(x, y), textLocalPos(0, 0)
{
}

BackrectText::~BackrectText()
{
}

void BackrectText::Draw(RenderWindow &window)
{
	RectangleObj::Draw(window);
	window.draw(text);
}

void BackrectText::SetPos(const Vector2f &pos)
{
	RectangleObj::SetPos(pos);
	text.setPosition(position + textLocalPos);
}

void BackrectText::SetOrigin(Origins origin)
{
	RectangleObj::SetOrigin(origin);
	Utils::SetOrigin(text, origin);
}

void BackrectText::SetTextLocalPos(Vector2f localPos)
{
	textLocalPos = localPos;
	SetPos(position);
}

void BackrectText::SetTextStyle(Color textColor, int textSize, Color textOutlineColor, float textOutlineThickness)
{
	text.setFillColor(textColor);
	text.setCharacterSize(textSize);
	text.setOutlineColor(textOutlineColor);
	text.setOutlineThickness(textOutlineThickness);
}

void BackrectText::SetFont(Font &font)
{
	text.setFont(font);
}
