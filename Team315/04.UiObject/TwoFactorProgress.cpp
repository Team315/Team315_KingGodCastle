#include "TwoFactorProgress.h"

TwoFactorProgress::TwoFactorProgress(float x, float y)
	: ProgressBar(x, y), secondProgressValue(0.f)
{
	secondProgress.setFillColor(Color::White);
}

TwoFactorProgress::~TwoFactorProgress()
{
}

void TwoFactorProgress::Update(float dt)
{
}

void TwoFactorProgress::Draw(RenderWindow &window)
{
	window.draw(shape);
	window.draw(progress);
	window.draw(secondProgress);
}

void TwoFactorProgress::SetPos(const Vector2f &pos)
{
	ProgressBar::SetPos(pos);
	secondProgress.setPosition(pos.x + shapeSize.x, pos.y + shapeSize.y);
	Utils::SetOrigin(secondProgress, Origins::TR);
}

void TwoFactorProgress::SetSize(float x, float y)
{
	ProgressBar::SetSize(x, y);

}

void TwoFactorProgress::UpdateProgress()
{
	progressSize =
		Vector2f(shapeSize.x * progressValue, shapeSize.y);
	secondProgress.setSize(progressSize);
}

void TwoFactorProgress::SetSecondProgressColor(Color color)
{
	secondProgress.setFillColor(color);
}

void TwoFactorProgress::SetSecondProgressValue(float value)
{
	secondProgressValue = value;
	secondProgressValue = Utils::Clamp(secondProgressValue, 0.f, 1.f);
}

void TwoFactorProgress::TranslateProgress(float value)
{
	secondProgressValue += value;
	secondProgressValue = Utils::Clamp(secondProgressValue, 0.f, 1.f);
}