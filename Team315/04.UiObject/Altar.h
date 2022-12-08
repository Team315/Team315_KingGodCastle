#pragma once
#include "SpriteObj.h"
#include "TextObj.h"
#include "Include.h"

class Altar :  public SpriteObj

{
protected:
	SpriteObj m_altarEffect;
	SpriteObj m_altarLight;
	//roma
	SpriteObj m_romaNum01;
	SpriteObj m_romaNum05;
	SpriteObj m_romaNum10;
	SpriteObj m_romaNum15;
	//dot
	SpriteObj m_romaNum02;
	SpriteObj m_romaNum03;
	SpriteObj m_romaNum04;
	SpriteObj m_romaNum06;
	SpriteObj m_romaNum07;
	SpriteObj m_romaNum08;
	SpriteObj m_romaNum09;
	SpriteObj m_romaNum11;
	SpriteObj m_romaNum12;
	SpriteObj m_romaNum13;
	SpriteObj m_romaNum14;

	TextObj m_number;
	TextObj m_altarName;
	Vector2f altarPos;
	int m_Index;


public:
	Altar(Vector2f mainPos, int index);
	~Altar();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void MoveSetPos(Vector2f movepos);
	int GetIndex() { return m_Index; };
	void SetRomaNumber(Vector2f mainPos, int index);
	void SetDot(Vector2f mainPos, int index);
};

