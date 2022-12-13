#pragma once
#include "RectangleObj.h"

class SpriteObj;

class EventPanel : public RectangleObj
{
protected:
	SpriteObj* previewButton;

public:
	EventPanel();
	virtual ~EventPanel();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};