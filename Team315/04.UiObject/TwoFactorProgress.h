#pragma once
#include "ProgressBar.h"

class TwoFactorProgress : public ProgressBar
{
protected:
	RectangleShape secondProgress;
	Vector2f secondProgressSize;
	float secondProgressValue;

public:
	TwoFactorProgress(float x = 0, float y = 0);
	virtual ~TwoFactorProgress();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow &window) override;
	virtual void SetPos(const Vector2f &pos) override;

	virtual void UpdateProgress() override;

	void SetSecondProgressColor(Color color);
	void SetSecondProgressValue(float value);
	const float GetSecondProgressValue() { return progressValue; }
	void SetRatio(float TotalAmount, float firstFactorAmount, float secondFactorAmount);
	
	virtual void TranslateProgress(float value) override;
};