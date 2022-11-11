#pragma once
#include "SpriteObj.h"

class RssTextWindow : public SpriteObj
{
protected:
	RectangleShape	background;
	Text			text;
	float			value;
	float			valueGoal;
	int				length;
	
	Vector2f		localPos;
	Vector2f		bgLocalPos;
	Vector2f		txtLocalPos;

public:
	RssTextWindow(Font& font);
	virtual ~RssTextWindow();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetSize(Vector2f size);
	void SetBackgroundColor(Color color);
	void SetBackgroundOutline(Color color, float thickness);

	void SetBackLocalPos(Vector2f pos);
	void SetTextLocalPos(Vector2f pos);
	void SetTextValue(float value);
	void SetTextStyle(Color color, int cSize);
	void SetTextOutline(Color color, float thickness);
	void SetGoal(float goal);
	float GetValue() { return value; }
	float GetValueGoal() { return valueGoal; }

	string MakeFormat(float value);
};