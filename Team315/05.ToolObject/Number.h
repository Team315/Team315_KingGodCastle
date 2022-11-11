#pragma once
#include "SpriteObj.h"

class Number : public SpriteObj
{
protected:
	Sprite m_BeforeNum;
	Sprite m_AffterNum;
	int m_index;

public:
	Number();
	~Number();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	string SetPath(int num);
	void SetNum(Vector2f pos, int beforeNum, int affterNum, int index);
	//void SetOrigins(Origins origin);

	bool CollideTest(Vector2f pos);
};
