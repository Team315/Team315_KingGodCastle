#pragma once
#include "Button.h"

class SpriteButton : public Button
{
protected:
	Sprite btnSprite;
	Vector2f btnSpriteLocalPos;

public:
	SpriteButton();
	virtual ~SpriteButton();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetOrigin(Origins origin) override;

	void SetButton(Texture& backTexture,
		Font& font, wstring textString,
		Texture& buttonTexture,
		float btnTextLocalPosX = 0, float btnTextLocalPosY = 0,
		float posX = 0, float posY = 0,
		float scaleX = 1.f, float scaleY = 1.f,
		Color baseColor = Color::White,
		Color hoverColor = Color::Red,
		Color textColor = Color::Black,
		int textSize = 25);

	void SetButtonSize(float sizeX, float sizeY);
	void SetBtnSpriteLocalPos(float sizeX, float sizeY);
	void SetButtonTextColor(Color textColor, Color outlineColor, float OutlineThickness);
};