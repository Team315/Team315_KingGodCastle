#include "RssProgressWindow.h"

RssProgressWindow::RssProgressWindow()
{
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
}

void RssProgressWindow::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	progress.SetPos(pos + progressLocalPos);
}

void RssProgressWindow::SetSize(Vector2f size)
{
	progress.SetSize(size.x, size.y);
}

void RssProgressWindow::SetProgressLocalPos(Vector2f prgPos)
{
	progressLocalPos = prgPos;
}

void RssProgressWindow::SetColor(Color backColor, Color prgColor, Color prgBackColor, float thickness)
{
	progress.SetBackgroundColor(backColor);
	progress.SetProgressColor(prgColor);
	progress.SetBackgroundOutline(prgBackColor, thickness);
}