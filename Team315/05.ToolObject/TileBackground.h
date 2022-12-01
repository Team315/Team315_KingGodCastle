#pragma once
#include "SpriteObj.h"
#include "Include.h"

class TileBackground : public SpriteObj
{
protected:
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

	void SetTilePlay(Vector2i indexArr, Vector2f pos, int index, TileTypes TileTypes);

	bool CollisionCheck(Vector2f pos, int index);
	bool OnEdge(bool isCollAble);
};

