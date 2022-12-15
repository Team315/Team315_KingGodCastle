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

	//Brazier m_brazier;
	Vector2f testPos;
	vector<Altar*>  AltarList;
	vector<Brazier*>  BrazierList;
	RssProgressWindow* levelBar;

public:
	AltarScene();
	~AltarScene();

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

