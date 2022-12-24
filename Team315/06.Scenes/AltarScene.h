#pragma once
#include "Scene.h"
#include "Include.h"

class Brazier;
class Altar;
class RssProgressWindow;

class AltarScene : public Scene
{
protected:
	SpriteObj* m_backGround;
	SpriteObj m_backButton;

	vector<Altar*>  AltarList;
	Brazier*  brazier;
	RssProgressWindow* levelBar;

	// instruction
	Sprite altarInstruction;
	bool isAltarInstruction;
	Sprite altarExpInstruction;
	bool isAltarExpInstruction;
	Sprite altarResetInstruction;
	bool isAltarResetInstruction;

public:
	AltarScene();
	virtual ~AltarScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CallButton();
	void IsSize(bool is);
	void SetAltar();
	void SetBrazier();

	void SaveData();
};