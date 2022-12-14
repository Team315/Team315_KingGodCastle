#pragma once
#include "SpriteObj.h"

class BackgroundText : public SpriteObj
{
protected:
	Text text;
	Vector2f textLocalPos;

public:
	BackgroundText();
	virtual ~BackgroundText();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetOrigin(Origins origin) override;

	void SetTextLocalPos(Vector2f localPos);
	void SetTextStyle(Color textColor, int textSize, Color textOutlineColor, float textOutlineThickness);
	void SetFont(Font &font);
	void SetString(wstring str);
	void SetString(string str);
	void SetString(float num);
};