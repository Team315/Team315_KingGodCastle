#pragma once
#include "SpriteObj.h"

class RssProgressWindow;
class TextObj;
class RectangleObj;
class InfoWindow : public SpriteObj
{
protected:
	RectangleObj m_Background;

	SpriteObj m_backButton;

	SpriteObj m_altar0;
	SpriteObj m_altar1;
	SpriteObj m_altar2;
	SpriteObj m_altar3;

	TextObj m_Textaltar0;
	TextObj m_Textaltar1;
	TextObj m_Textaltar2;
	TextObj m_Textaltar3;

	RssProgressWindow* levelBar;

	vector<Sprite> powerUpSprites;
	vector<RectangleShape> rectangleShapes;

	bool isOnOff;
public:
	InfoWindow();
	~InfoWindow();

	virtual void Enter();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	bool CollCall(Vector2f mousepos);
	bool CollBackButton(Vector2f mousepos);
};

