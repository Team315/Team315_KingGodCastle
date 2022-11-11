#pragma once
#include "SpriteObj.h"


class Theme : public SpriteObj
{
protected:
	int m_index;
public:
	Theme();
	~Theme();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTheme(Vector2f pos, int index);
	string SetPath(int num);
};

