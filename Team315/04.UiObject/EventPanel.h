#pragma once
#include "RectangleObj.h"

class BackgroundText;
class Scene;
class SpriteObj;

class EventPanel : public RectangleObj
{
protected:
	SpriteObj* previewButton;
	Scene* parentScene;
	bool previewOn;
	Sprite head;
	Vector2f headLocalPos;
	BackgroundText* title;

public:
	EventPanel(Scene* scene);
	virtual ~EventPanel();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetOrigin(Origins origin) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetEventPanelType(EventType eType);
};