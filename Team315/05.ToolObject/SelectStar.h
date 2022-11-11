#pragma once
#include "SpriteObj.h"
#include "Include.h"

class SelectStar : public SpriteObj
{
protected:
	Sprite m_star;
	int m_grade;

public:
	SelectStar();
	~SelectStar();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSelectStar(Vector2f pos, int grade);
	string SetPath(int grade);
};

