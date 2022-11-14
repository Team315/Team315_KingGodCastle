#pragma once
#include "SpriteObj.h"
#include "Include.h"

class TilePlay :public SpriteObj
{
protected:
	Sprite m_Obstacle;
	RectangleShape m_playerArea;

	TileTypes m_TileTypes;

	Vector2i m_index;
	bool isCollAble;

public:
	TilePlay();
	~TilePlay();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTilePlay(Vector2i index, Vector2f pos, int count, TileTypes TileTypes);
	void SetObstacle();

};

