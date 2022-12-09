#pragma once
#include "Scene.h"
#include "Include.h"

class Altar;
class RectangleObj;
class AltarScene : public Scene
{
protected:
	RectangleObj* m_backGround;

	Vector2f testPos;
	vector<Altar*>  AltarList;

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

};

