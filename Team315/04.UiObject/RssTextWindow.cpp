#include "RssTextWindow.h"

RssTextWindow::RssTextWindow(Font& font)
	: value(0.f), valueGoal(0.f), length(10)
{
	text.setFont(font);
	Utils::SetOrigin(text, Origins::MR);
}

RssTextWindow::~RssTextWindow()
{
}

void RssTextWindow::Update(float dt)
{
	text.setString(MakeFormat(value));
	if (!Utils::EqualFloat(value, valueGoal))
	{
		if (value <= valueGoal)
			value += (valueGoal - value + 1) * dt;
		else
			value -= (value - valueGoal) * dt;

		if (Utils::EqualFloat(value, valueGoal))
			value = valueGoal;
	}
}

void RssTextWindow::Draw(RenderWindow& window)
{
	window.draw(background);
	window.draw(text);
	SpriteObj::Draw(window);
}

void RssTextWindow::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	background.setPosition(pos + bgLocalPos);
	text.setPosition(pos + txtLocalPos);
}

void RssTextWindow::SetSize(Vector2f size)
{
	background.setSize(size);
}

void RssTextWindow::SetBackgroundColor(Color color)
{
	background.setFillColor(color);
}

void RssTextWindow::SetBackgroundOutline(Color color, float thickness)
{
	background.setOutlineColor(color);
	background.setOutlineThickness(thickness);
}

void RssTextWindow::SetBackLocalPos(Vector2f pos)
{
	bgLocalPos = pos;
}

void RssTextWindow::SetTextLocalPos(Vector2f pos)
{
	txtLocalPos = pos;
}

void RssTextWindow::SetTextValue(float value)
{
	valueGoal = value;
}

void RssTextWindow::SetTextStyle(Color color, int cSize)
{
	text.setFillColor(color);
	text.setCharacterSize(cSize);
}

void RssTextWindow::SetTextOutline(Color color, float thickness)
{
	text.setOutlineColor(color);
	text.setOutlineThickness(thickness);
}

void RssTextWindow::SetGoal(float goal)
{
	if (goal < 0)
		goal = 0;
	valueGoal = goal;
}

string RssTextWindow::MakeFormat(float value)
{
	string ret(length, ' ');
	int iVal = (int) value;
	int idx = length - 1;
	if (iVal == 0)
	{
		ret[idx] = '0';
	}
	else
	{
		while (iVal)
		{
			ret[idx] = iVal % 10 + '0';
			iVal /= 10;
			idx--;
		}
	}
	return ret;
}