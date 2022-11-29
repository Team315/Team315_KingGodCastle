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
	UpdateProgress();
}

void TwoFactorProgress::Draw(RenderWindow &window)
{
	ProgressBar::Draw(window);
	window.draw(secondProgress);
}

void TwoFactorProgress::SetPos(const Vector2f &pos)
{
	progressSize =
		Vector2f(shapeSize.x * progressValue, shapeSize.y);
	progress.setSize(progressSize);
}

void TwoFactorProgress::UpdateProgress()
{
	ProgressBar::UpdateProgress();
	secondProgressSize =
		Vector2f(shapeSize.x * secondProgressValue, shapeSize.y);
	secondProgress.setPosition(position.x + progressSize.x, position.y);
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

void TwoFactorProgress::SetRatio(float TotalAmount,
	float firstFactorAmount, float secondFactorAmount)
{
	float firstValue = 0.f, secondValue = 0.f;
	float sumFactors = firstFactorAmount + secondFactorAmount;
	if (TotalAmount < sumFactors)
	{
		firstValue = firstFactorAmount / sumFactors;
		secondValue = secondFactorAmount / sumFactors;
	}
	else
	{
		firstValue = firstFactorAmount / TotalAmount;
		secondValue = secondFactorAmount / TotalAmount;
	}
	SetProgressValue(firstValue);
	SetSecondProgressValue(secondValue);
}

void TwoFactorProgress::TranslateProgress(float value)
{
	secondProgressValue += value;
	secondProgressValue = Utils::Clamp(secondProgressValue, 0.f, 1.f);
}