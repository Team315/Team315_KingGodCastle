#pragma once
#include "SpriteObj.h"
#include "Include.h"
#include "FileData.h"

using namespace ns;

class TilePlay :public SpriteObj
{
protected:
	Sprite m_Obj;
	RectangleShape m_playerArea;

	TileInfo m_TileInfo;

	ns::TileData m_TileData;

	TileTypes m_TileTypes;
	ThemeTypes m_ThemeTypes;
	int m_PathIndex;

	Vector2i m_index;
	int m_chapterIndex;
	bool isCollAble;

	Object* onTileObj;
public:
	TilePlay();
	virtual ~TilePlay();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTilePlay(Vector2i indexArr , Vector2f pos, int index, TileTypes TileTypes, int grade);
	void SetObstacle(ThemeTypes themeTypes, int obstacleIndex);
	string GetObstaclePath(ThemeTypes types, int num);
	void SetMonster(ThemeTypes themeTypes, int monsterIndex, int grade);
	string GetMonsterName(ThemeTypes types, int num);
	void SetEraser();

	void SetTileData(ns::TileData TileData);

	TileInfo GetTileInfo();
	TileData GetTileData();

	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeAlpha(bool check);
};