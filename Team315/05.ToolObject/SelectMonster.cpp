#include "SelectMonster.h"

SelectMonster::SelectMonster(MonsterTypes monsterTypes)
	: m_monsterTypes(monsterTypes)
{
	switch (m_monsterTypes)
	{
	case MonsterTypes::Monster:
		sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/monster/edge_monster.png"));
		break;
	case MonsterTypes::Boss:
		sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/monster/edge_boss.png"));
		break;
	}
}

SelectMonster::~SelectMonster()
{
}

void SelectMonster::Init()
{
}

void SelectMonster::Release()
{
}

void SelectMonster::Update(float dt)
{
}

void SelectMonster::Draw(RenderWindow& window)
{
}

void SelectMonster::SetSelectMonster(Vector2f pos, ThemeTypes types, int index)
{
	//
}

string SelectMonster::SetPath(ThemeTypes types, int num)
{

	switch (m_monsterTypes)
	{
	case MonsterTypes::Monster:
		sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/monster/edge_monster.png"));
		break;
	case MonsterTypes::Boss:
		sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/monster/edge_boss.png"));
		break;
	}

	m_index = num;
	string field = to_string((int)types / 10) + to_string((int)types % 10);

	string path = "graphics/TileSet/Field_" + field + "/field_" + field + "_";
	string sNum = to_string(m_index / 10) + to_string(m_index % 10);
	string png = ".png";

	return path + sNum + png;
}
