#pragma once
#include "RectangleObj.h"

class BackgroundText;
class BackrectText;
class Scene;
class SpriteObj;
class SpriteGrid;
class ItemInfoWindow;

class EventPanel : public RectangleObj
{
protected:
	SpriteObj* previewButton;
	Scene* parentScene;
	bool previewOn;
	Sprite head;
	Vector2f headLocalPos;
	BackgroundText* title;
	vector<SpriteObj*> frames;
	vector<SpriteGrid*> sprites;
	vector<SpriteObj*> items;
	ItemInfoWindow* infoWindow;
	EventType eventType;
	int curTier;
	BackrectText* rerollButton;
	BackrectText* selectButton;
	bool selectItem;
	int selectIdx;
	Sprite rerollCountSprite;
	BackrectText* expResultWindow;

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

	void SetEventPanelType(EventType eType, int tier = 0);
	EventType GetEventType() { return eventType; }
	void SetEventType(EventType eType) { eventType = eType; }
	SpriteObj* GetPreviewButton() { return previewButton; }
	BackrectText* GetSelectButton() { return selectButton; }
	void SetRerollText(int num);
	void SetExpResultString(int num);
};