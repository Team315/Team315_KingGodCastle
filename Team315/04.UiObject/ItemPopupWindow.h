#pragma once
#include "SpriteGrid.h"

class ItemPopupWindow : public SpriteGrid
{
protected:

public:
	ItemPopupWindow(float x = 0, float y = 0);
	virtual ~ItemPopupWindow();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetOrigin(Origins origin) override;
	virtual void SetPos(const Vector2f& pos) override;
};