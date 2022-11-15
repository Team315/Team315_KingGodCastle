#pragma once
#include "SpriteObj.h"

class TilePlay :public SpriteObj
{
protected:
	Sprite m_Obstacle;
	
	Vector2i m_index;
	bool isCollAble;

public:
	TilePlay();
	~TilePlay();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTilePlay(Vector2i index, Vector2f pos, int count);

};

