#pragma once
#include "SpriteObj.h"

class RssTextWindow : public SpriteObj
{
protected:
	RectangleShape background;
	Text text;
	float value;
	float valueGoal;

	Vector2f	backgroundLocalPos;
	Vector2f	textLocalPos;

public:
	RssTextWindow(Font& font);
	virtual ~RssTextWindow();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetSize(float x, float y);
	void SetBackgroundColor(Color color);
	void SetBackgroundOutline(Color color, float thickness);

	void SetBackgroundLocalPos(Vector2f bgPos);
	void SetTextLocalPos(Vector2f txtPos);
	void SetTextValue(float value);
	void SetTextStyle(Color color, int cSize);
	void SetTextOutline(Color color, float thickness);
};