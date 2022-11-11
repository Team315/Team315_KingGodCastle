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
	SpriteObj::Draw(window);
	window.draw(m_monster);
}

void SelectMonster::SetSelectMonster(Vector2f pos, ThemeTypes types, int index)
{
	sprite.setPosition(pos);
	SetOrigin(Origins::MC);

	m_monster.setTexture(*RESOURCE_MGR->GetTexture(SetPath(types, index)));
	m_monster.setPosition(pos);
	Utils::SetOrigin(m_monster, Origins::MC);
}

string SelectMonster::SetPath(ThemeTypes types, int num)
{
	string path;
	m_index = num;

	switch (m_monsterTypes)
	{
	case MonsterTypes::Monster:
		path = "graphics/ToolUi/monster/Monster";
		break;
	case MonsterTypes::Boss:
		path = "graphics/ToolUi/monster/Boss";
		break;
	}

	string field = to_string((int)types / 10) + to_string((int)types % 10)+"_";
	string sNum = to_string(m_index / 10) + to_string(m_index % 10);
	string png = ".png";

	return path+ field + sNum + png;
}
