#pragma once
#include "SpriteObj.h"
#include "Include.h"

class TilePlay :public SpriteObj
{
protected:
	Sprite m_Obj;
	RectangleShape m_playerArea;

	TileTypes m_TileTypes;

	Vector2i m_index;
	int m_chapterIndex;
	int m_stateIndex;
	bool isCollAble;

public:
	TilePlay();
	~TilePlay();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTilePlay(Vector2i index, Vector2f pos, int count, TileTypes TileTypes);
	void SetObstacle(ThemeTypes themeTypes, int obstacleIndex);
	string SetObstaclePath(ThemeTypes types, int num);
	void SetMonster(ThemeTypes themeTypes, int monsterIndex);
	string SetMonsterPath(ThemeTypes types, int num);
	void SetEraser();

	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeAlpha(bool check);
};

