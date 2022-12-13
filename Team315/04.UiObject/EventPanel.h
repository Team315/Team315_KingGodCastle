#pragma once
#include "SpriteObj.h"

class EventPanel : public SpriteObj
{
protected:

public:
	EventPanel();
	virtual ~EventPanel();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};