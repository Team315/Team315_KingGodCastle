#pragma once
#include "UIMgr.h"
#include "SpriteButton.h"
#include "Include.h"
#include <vector>

class HUD : public Object
{
protected:
	enum class buttonMode
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

public:
	HUD();
	virtual ~HUD();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	vector<SpriteButton*> buttons;
	int GetTabSize() { return tabSize; }
};

class LobySceneUI : public UIMgr
{
protected:
	HUD* hud;

public:
	LobySceneUI(Scene* scene);
	virtual ~LobySceneUI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	HUD* GetHud() { return hud; }
};