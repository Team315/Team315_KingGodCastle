#pragma once
#include "UIMgr.h"
#include "Button.h"

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
	//HUD hud;

public:
	MainSceneUI(Scene* scene);
	virtual ~MainSceneUI();

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};