#pragma once
#include "SpriteObj.h"
#include "Include.h"

class SelectTile : public SpriteObj
{
protected:
	ThemeTypes m_types;
	int m_index;

public:
	SelectTile();
	~SelectTile();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSelectTile(Vector2f pos, ThemeTypes types, int index);
	string SetPath(ThemeTypes types, int num);

};