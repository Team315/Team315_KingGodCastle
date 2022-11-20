#pragma once
#include "SpriteObj.h"
#include "FileData.h"
#include "Include.h"

class Tile : public SpriteObj
{
protected:
	Sprite m_obstacle;
	Vector2f m_pos;
	ns::TileData m_tileData;
	RectangleShape m_playerArea;

public:
	Tile();
	~Tile();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateTile(ns::TileData tileData);
	void SetObstacle(ThemeTypes themeTypes, int obstacleIndex);
	string SetObstaclePath(ThemeTypes types, int num);
	void SetMonster(ThemeTypes themeTypes, int monsterIndex, int grade);
	string SetMonsterPath(ThemeTypes types, int num);
};

