#include "ProgressBar.h"
#include "Include.h"

ProgressBar::ProgressBar(float x, float y)
	: RectangleObj(x, y), progressValue(0.f)
{
	shapeSize = Vector2f(x, y);
	progress.setFillColor(Color::White);
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Update(float dt)
{
	UpdateProgress();
}

void ProgressBar::Draw(RenderWindow& window)
{
	Object::Draw(window);
	window.draw(shape);
	window.draw(progress);
}

void ProgressBar::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	progress.setPosition(position);
}

void ProgressBar::SetSize(float x, float y)
{
	shapeSize = Vector2f(x, y);
	RectangleObj::SetSize(x, y);
}

void ProgressBar::UpdateProgress()
{
	progressSize =
		Vector2f(shapeSize.x * progressValue, shapeSize.y);
	progress.setSize(progressSize);
}

void ProgressBar::SetBackgroundColor(Color color)
{
	shape.setFillColor(color);
}

void ProgressBar::SetBackgroundOutline(Color color, float thickness)
{
	shape.setOutlineColor(color);
	shape.setOutlineThickness(thickness);
}

void ProgressBar::SetProgressColor(Color color)
{
	progress.setFillColor(color);
}

void ProgressBar::SetProgressValue(float value)
{
	progressValue = value;
	progressValue = Utils::Clamp(progressValue, 0.f, 1.f);
}

void ProgressBar::TranslateProgress(float value)
{
	progressValue += value;
	progressValue = Utils::Clamp(progressValue, 0.f, 1.f);
}