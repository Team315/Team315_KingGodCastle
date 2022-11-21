#pragma once
#include "SpriteObj.h"
#include "FileData.h"
#include "Include.h"

class Tile : public SpriteObj
{
protected:
	ns::TileData m_tileData;
	RectangleShape m_playerArea;

public:
	Tile();
	virtual ~Tile();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateTile(ns::TileData tileData);
	string GetObstaclePath();
	string GetMonsterName();
	ns::TileData& GetTileData() { return m_tileData; }
};