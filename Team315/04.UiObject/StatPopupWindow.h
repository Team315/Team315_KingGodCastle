#pragma once
#include "RectangleObj.h"

class BackrectText;
class BackgroundText;
class Character;
class ProgressBar;

class StatPopupWindow : public RectangleObj
{
protected:
	// always
	BackrectText* nameText;
	BackgroundText * starText;

	Sprite portrait;
	RectangleShape portraitRect;

	BackrectText* adText;
	BackrectText* apText;
	BackrectText* asText;
	Sprite adImg;
	Sprite apImg;
	Sprite asImg;
	ProgressBar* hpBar;
	Text currentHp;
	
	bool useOptional;
	// optional
	ProgressBar* mpBar;

public:
	StatPopupWindow(float x = 0, float y = 0);
	virtual ~StatPopupWindow();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetOrigin(Origins origin) override;

	void SetCharacter(Character* character);
};