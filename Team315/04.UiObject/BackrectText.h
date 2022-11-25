#pragma once
#include "RectangleObj.h"

class BackrectText : public RectangleObj
{
protected:
	Text text;
	Vector2f textLocalPos;

public:
	BackrectText(float x = 0.f, float y = 0.f);
	virtual ~BackrectText();

	virtual void Draw(RenderWindow &window) override;
	virtual void SetPos(const Vector2f &pos) override;
	virtual void SetOrigin(Origins origin) override;

	void SetTextLocalPos(Vector2f localPos);
	void SetTextStyle(Color textColor, int textSize, Color textOutlineColor, float textOutlineThickness);
	void SetFont(Font& font);
};