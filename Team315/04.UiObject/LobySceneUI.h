#pragma once
#include "UIMgr.h"
#include <vector>

class Button;
class Character;
class SpriteButton;
class SpriteObj;
class RectangleObj;
class RssProgressWindow;
class RssTextWindow;

class LobySceneUI : public UIMgr
{
protected:
	// bottom tab
	enum class buttonModeEnum
	{
		none = -1,
		shop,
		barrack,
		gate,
		altar,
		mode,
		count,
	};

	// top resources
	enum class gameResourceEnum
	{
		none = -1,
		level,
		gold,
		jewel,
		count,
	};

	// HUD
	vector<SpriteButton*> buttons;
	int tabSize;
	float buttonSize;

	RssProgressWindow* expWind;
	RssTextWindow* goldWind;
	RssTextWindow* jewelWind;
	int gameResourceCount;

	// shop tab
	RectangleObj* shopBackgroundOverlay;
	vector<SpriteObj*> shopIllusts;

	// barrack tab
	vector<RectangleObj*> barrackPresetRect; // Draw only rect
	vector<Character*> preset; // Container to reference in GameManager
	RectangleObj* heroTabBackground;
	vector<RectangleObj*> heroTabRect;
	vector<Character*> heroTab;

	// gate tab
	vector<Character*> gatePreset;
	Button* startBtn;

public:
	LobySceneUI(Scene* scene);
	virtual ~LobySceneUI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetOrigin(Origins origin) override;

	int GetTabSize() { return tabSize; }
	vector<SpriteButton*> GetButtons() { return buttons; }
	RssProgressWindow* GetExpWindow() { return expWind; }
	RssTextWindow* GetGoldWindow() { return goldWind; }
	RssTextWindow* GetJewelWindow() { return jewelWind; }
	Button* GetStartButton() { return startBtn; }
};