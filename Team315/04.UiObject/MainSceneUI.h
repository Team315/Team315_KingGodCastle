#pragma once
#include "UIMgr.h"
#include "Button.h"
#include "SpriteObj.h"
#include <vector>

class HUD
{
protected:
	Button* a;
	Button* b;
	Button* c;
	Button* d;
	Button* e;

public:

};

class MainSceneUI : public UIMgr
{
protected:
	vector<SpriteObj*> backgrounds;
	int tabCount;
	int currentBackground;
	//HUD hud;

public:
	MainSceneUI(Scene* scene);
	virtual ~MainSceneUI();

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void DrawBackground(RenderWindow& window);
};