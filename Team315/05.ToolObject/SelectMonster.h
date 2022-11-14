#pragma once
#include "SpriteObj.h"
#include "Include.h"
class SelectMonster :public SpriteObj
{
protected:
	Sprite m_monster;
	RectangleShape m_Edge;

	MonsterTypes m_monsterTypes;

	int m_index;
	bool isEdge;


public:
	SelectMonster(MonsterTypes monsterTypes);
	~SelectMonster();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSelectMonster(Vector2f pos, ThemeTypes types, int index);
	string SetPath(ThemeTypes types, int num);

	int GetIndex();

	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeSize(bool check);
	void OnEdge(int index);
};

