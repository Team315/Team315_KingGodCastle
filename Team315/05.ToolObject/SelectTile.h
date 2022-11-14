#pragma once
#include "SpriteObj.h"
#include "Include.h"

class SelectTile : public SpriteObj
{
protected:
	RectangleShape m_Edge;

	ThemeTypes m_types;
	int m_index;
	bool isEdge;

public:
	SelectTile();
	~SelectTile();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSelectTile(Vector2f pos, ThemeTypes types, int index);
	string SetPath(ThemeTypes types, int num);
	int GetIndex();
	ThemeTypes GetThemeTypes();

	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeColor(bool check);
	void OnEdge(int index);
};