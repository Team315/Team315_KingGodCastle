#pragma once
#include "SpriteObj.h"
#include "Include.h"

class SelectObstacle : public SpriteObj
{
	ThemeTypes m_types;
	int m_index;

public:
	SelectObstacle();
	~SelectObstacle();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSelectObstacle(Vector2f pos, ThemeTypes types, int index);
	string SetPath(ThemeTypes types, int num);


};

