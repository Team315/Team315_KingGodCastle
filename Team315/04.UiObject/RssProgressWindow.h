#pragma once
#include "SpriteObj.h"
#include "ProgressBar.h"

class RssProgressWindow : public SpriteObj
{
protected:
	ProgressBar progress;

	Vector2f	progressLocalPos;

public:
	RssProgressWindow();
	virtual ~RssProgressWindow();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetSize(Vector2f size);
	void SetProgressLocalPos(Vector2f prgPos);
	void SetColor(Color backColor, Color prgColor, Color prgBackColor = Color::Black, float thickness = 0.f);
	ProgressBar& GetProgressBar() { return progress; }
};