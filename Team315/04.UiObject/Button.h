#pragma once
#include "SpriteObj.h"

class Button : public SpriteObj
{
protected:
	Text buttonText;
	Vector2f buttonTextDelta;
	Color baseColor;
	Color hoverColor;

public:
	Button();
	virtual ~Button();

	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;

	void SetButton(Texture& texture,
		Font& font, string textString,
		float txtDeltaPosX = 0, float txtDeltaPosY = 0,
		float posX = 0, float posY = 0,
		float scaleX = 1.f, float scaleY = 1.f,
		Color baseColor = Color::White,
		Color hoverColor = Color::Red, 
		Color textColor = Color::Black,
		int textSize = 25);

	void SetButtonSize(float sizeX, float sizeY);
	bool CollideTest(Vector2f pos);
	Color GetBaseColor() { return baseColor; }
	Color GetHoverColor() { return hoverColor; }
};