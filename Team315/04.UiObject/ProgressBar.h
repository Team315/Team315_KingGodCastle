#pragma once
#include "RectangleObj.h"

class ProgressBar : public RectangleObj
{
protected:
	RectangleShape progress;
	Vector2f shapeSize;
	Vector2f progressSize;
	float progressValue;

public:
	ProgressBar(float x = 0, float y = 0);
	virtual ~ProgressBar();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetOrigin(Origins origin) override;

	virtual void SetSize(float x, float y);
	virtual void UpdateProgress();

	void SetBackgroundColor(Color color);
	void SetBackgroundOutline(Color color, float thickness);
	void SetProgressColor(Color color);
	void SetProgressValue(float value);
	const float GetProgressValue() { return progressValue; }
	
	virtual void TranslateProgress(float value);
};