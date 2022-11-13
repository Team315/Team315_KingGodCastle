#pragma once
#include "SpriteObj.h"
#include "Include.h"

class SelectObstacle : public SpriteObj
{
	RectangleShape m_Edge;

	ThemeTypes m_types;
	int m_index;
	bool isEdge;

public:
	SelectObstacle();
	~SelectObstacle();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSelectObstacle(Vector2f pos, ThemeTypes types, int index);
	string SetPath(ThemeTypes types, int num);

	int GetIndex();

	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeColor(bool check);
	void OnEdge(int index);
};

