#pragma once
#include "SpriteObj.h"
#include "Include.h"

class RectangleObj;
class TileBackground : public SpriteObj
{
protected:
	RectangleObj m_rectHit;

	BackGroundData backGroundData;
	TileTypes m_TileTypes;
	ThemeTypes m_ThemeTypes;

	bool isCollAble;

public:
	TileBackground();
	~TileBackground();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTileBackground(Vector2i indexArr, Vector2f pos);

	bool CollisionCheck(Vector2f pos, int index);
	bool OnEdge(bool isCollAble);
};

