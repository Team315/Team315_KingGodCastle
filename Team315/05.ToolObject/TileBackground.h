#pragma once
#include "SpriteObj.h"
#include "Include.h"
#include "RectangleObj.h."

class TileBackground : public SpriteObj
{
protected:
	RectangleObj m_rectHit;

	BackGroundData backGroundData;
	TileTypes m_TileTypes;
	ThemeTypes m_ThemeTypes;

	bool m_isCollAble;

public:
	TileBackground();
	~TileBackground();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTileBackground(Vector2i indexArr, Vector2f pos, int chapter);

	bool CollisionCheck(Vector2f pos);
	bool OnEdge(bool isCollAble);
	int GetChapther() { return (int)m_ThemeTypes; };
	void ChangeTileBackground(ThemeTypes types, int index);
	string GetBackgroundPath(ThemeTypes types, int num);
	BackGroundData GetBackGroundData() { return backGroundData; }

};

