#pragma once
#include "SpriteObj.h"
#include "TextObj.h"
#include "Include.h"
class Brazier : public SpriteObj
{
protected:
	int m_grade;

	SpriteObj m_maxLevelSprite;
	SpriteObj m_collectSprite;

	
public:
	Brazier();
	~Brazier();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void MoveSetPos(Vector2f movepos);
};

