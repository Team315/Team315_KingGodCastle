#pragma once
#include "UIMgr.h"
#include <vector>

class SpriteButton;
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
	int tabSize;
	float buttonSize;
	vector<SpriteButton*> buttons;

	// top resources
	enum class gameResourceEnum
	{
		none = -1,
		level,
		gold,
		jewel,
		count,
	};
	int gameResourceCount;
	RssProgressWindow* expWind;
	RssTextWindow* goldWind;
	RssTextWindow* jewelWind;

public:
	LobySceneUI(Scene* scene);
	virtual ~LobySceneUI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	int GetTabSize() { return tabSize; }
	vector<SpriteButton*> GetButtons() { return buttons; }
	RssProgressWindow* GetExpWindow() { return expWind; }
	RssTextWindow* GetGoldWindow() { return goldWind; }
	RssTextWindow* GetJewelWindow() { return jewelWind; }
};