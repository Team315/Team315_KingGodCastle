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
	window.draw(shape);
	window.draw(sprite);
	progress.Draw(window);

	Object::Draw(window);
}

void RssProgressWindow::SetPos(const Vector2f& pos)
{
	ResourceStatusWindow::SetPos(pos);
	progress.SetPos(pos + progressLocalPos);
}

void RssProgressWindow::SetSize(Vector2f size)
{
	shape.setSize(size);
	progress.SetSize(size.x, size.y);
}

void RssProgressWindow::SetProgressLocalPos(Vector2f prgPos)
{
	progressLocalPos = prgPos;
}

void RssProgressWindow::SetColor(Color backColor, Color prgColor)
{
	SetShapeColor(backColor);
	progress.SetProgressColor(prgColor);
}