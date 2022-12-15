#pragma once
#include "Scene.h"
#include "Include.h"

class Brazier;
class Altar;
class RectangleObj;
class RssProgressWindow;

class AltarScene : public Scene
{
protected:
	RectangleObj* m_backGround;
	//Brazier m_brazier;
	Vector2f testPos;
	vector<Altar*>  AltarList;
	vector<Brazier*>  BrazierList;
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
	~AltarScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetAltar();
	void SetBrazier();

	void SaveData();
};

