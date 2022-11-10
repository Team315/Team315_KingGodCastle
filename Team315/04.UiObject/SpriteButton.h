#pragma once
#include "Button.h"

class SpriteButton : public Button
{
protected:
	Sprite buttonSprite;
	Vector2f buttonSpriteSpacing;

public:
	SpriteButton();
	virtual ~SpriteButton();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetOrigin(Origins origin) override;

	void SetButton(Texture& backTexture,
		Font& font, wstring textString,
		Texture& buttonTexture,
		float txtSpacingPosX = 0, float txtSpacingPosY = 0,
		float posX = 0, float posY = 0,
		float scaleX = 1.f, float scaleY = 1.f,
		Color baseColor = Color::White,
		Color hoverColor = Color::Red,
		Color textColor = Color::Black,
		int textSize = 25);

	void SetButtonSize(float sizeX, float sizeY);
	void SetButtonSpriteSpacing(float sizeX, float sizeY);
};