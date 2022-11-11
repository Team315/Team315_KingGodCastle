#include "RssProgressWindow.h"
#include "Include.h"

RssProgressWindow::RssProgressWindow()
	: level(1)
{
	levelText.setFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	levelText.setString(to_string(level));
	levelText.setCharacterSize(20);
	levelText.setFillColor(Color::White);
	levelText.setOutlineColor(Color::Black);
	levelText.setOutlineThickness(2.f);
	Utils::SetOrigin(levelText, Origins::BR);
}

RssProgressWindow::~RssProgressWindow()
{
}

void RssProgressWindow::Update(float dt)
{
	progress.Update(dt);
}

void RssProgressWindow::Draw(RenderWindow& window)
{
	progress.Draw(window);
	SpriteObj::Draw(window);
	window.draw(levelText);
}

void RssProgressWindow::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	progress.SetPos(pos + progressLocalPos);
	levelText.setPosition(pos + levelTextLocalPos);
}

void RssProgressWindow::SetSize(Vector2f size)
{
	progress.SetSize(size.x, size.y);
}

void RssProgressWindow::SetProgressLocalPos(Vector2f pos)
{
	progressLocalPos = pos;
}

void RssProgressWindow::SetLevelTextLocalPos(Vector2f pos)
{
	levelTextLocalPos = pos;
	levelTextX = pos.x;
}

void RssProgressWindow::SetColor(Color backColor, Color prgColor, Color prgBackColor, float thickness)
{
	progress.SetBackgroundColor(backColor);
	progress.SetProgressColor(prgColor);
	progress.SetBackgroundOutline(prgBackColor, thickness);
}

void RssProgressWindow::SetLevel(int level)
{
	if (level == -1)
		this->level++;
	else
		this->level = level;
	if (this->level < 10)
		levelTextLocalPos.x = levelTextX;
	else
		levelTextLocalPos.x = levelTextX - 4;
	SetPos(position);
	levelText.setString(to_string(this->level));
}