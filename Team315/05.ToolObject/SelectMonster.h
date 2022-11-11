#pragma once
#include "SpriteObj.h"
#include "Include.h"
class SelectMonster :public SpriteObj
{
protected:
	Sprite m_monster;
	int m_index;
	MonsterTypes m_monsterTypes;

public:
	SelectMonster(MonsterTypes monsterTypes);
	~SelectMonster();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSelectMonster(Vector2f pos, ThemeTypes types, int index);
	string SetPath(ThemeTypes types, int num);
};

