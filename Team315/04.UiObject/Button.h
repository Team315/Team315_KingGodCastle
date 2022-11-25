#pragma once
#include "BackgroundText.h"

class Button : public BackgroundText
{
protected:
	Color baseColor;
	Color hoverColor;

public:
	Button();
	virtual ~Button();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetOrigin(Origins origin) override;

	void SetButton(Texture& backTexture,
		Font& font, wstring textString,
		float btnTextLocalPosX = 0, float btnTextLocalPosY = 0,
		float posX = 0, float posY = 0,
		float scaleX = 1.f, float scaleY = 1.f,
		Color baseColor = Color::White,
		Color hoverColor = Color::Red, 
		Color textColor = Color::Black,
		int textSize = 25);

	void SetButtonSize(float sizeX, float sizeY);
	void SetButtonStyle(Color baseColor, Color hoverColor);
	Color GetBaseColor() { return baseColor; }
	Color GetHoverColor() { return hoverColor; }
};