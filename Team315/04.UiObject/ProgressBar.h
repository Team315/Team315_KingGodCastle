#pragma once
#include "RectangleObj.h"

class ProgressBar : public RectangleObj
{
protected:
	RectangleShape progress;
	Vector2f shapeSize;
	Vector2f progressSize;

public:
	ProgressBar(float x = 0, float y = 0);
	virtual ~ProgressBar();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetSize(float x, float y);
	void UpdateProgress();
	void SetProgressColor(Color color);
	void SetProgressValue(float value);
	void TranslateProgress(float value);

	float progressValue;
};