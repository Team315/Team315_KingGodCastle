#pragma once
#include "RectangleObj.h"
#include "ProgressBar.h"
#include "BackgroundText.h"

class StatPopupWindow : public RectangleObj
{
protected:
	// always
	BackgroundText* nameText;
	BackgroundText* starText;

	Sprite portrait;
	Sprite adImg;
	Sprite apImg;
	Sprite asImg;
	ProgressBar* hpBar;
	
	// optional
	ProgressBar* mpBar;
	

public:
	StatPopupWindow(float x = 0, float y = 0);
	virtual ~StatPopupWindow();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetOrigin(Origins origin) override;
};