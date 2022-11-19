#pragma once
#include "SpriteObj.h"
class Star : public SpriteObj
{
protected:
	int m_grade;

public:
	Star();
	~Star();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetStar(FloatRect pos, int grade);
	string SetPath(int grade);

	void SetOnHeadPos(FloatRect pos, int grade);
};

