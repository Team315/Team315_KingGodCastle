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
	window.draw(m_Edge);
	window.draw(m_monster);
}

void SelectMonster::SetSelectMonster(Vector2f pos, ThemeTypes types, int index)
{
	m_index = index;

	cout << m_index << endl;

	sprite.setPosition(pos);
	SetOrigin(Origins::MC);

	m_monster.setTexture(*RESOURCE_MGR->GetTexture(SetPath(types, index)));
	m_monster.setPosition(pos);
	Utils::SetOrigin(m_monster, Origins::MC);

	FloatRect rect = sprite.getGlobalBounds();
	m_Edge.setSize({ rect.width,rect.height });
	m_Edge.setFillColor({ 0,0,0,0 });
	m_Edge.setPosition(pos);
	m_Edge.setOutlineThickness(-4.f);
	Utils::SetOrigin(m_Edge, Origins::MC);
}

string SelectMonster::SetPath(ThemeTypes types, int num)
{
	string path;

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

int SelectMonster::GetIndex()
{
	cout << m_index << endl;

	return m_index;
}

bool SelectMonster::CollisionCheck(Vector2f pos, int index)
{
	return ChangeSize(sprite.getGlobalBounds().contains(pos));
}

bool SelectMonster::ChangeSize(bool check)
{
	if (check)
	{
		m_monster.setScale({ 1.3f,1.3f });
		return true;
	}
	else
	{
		m_monster.setScale({ 1.f,1.f });
		return false;
	}
}

void SelectMonster::OnEdge(int index)
{
	if (m_index == index)
	{
		Color color;


		color.b = 255;

		m_Edge.setOutlineColor(color);

		isEdge = true;
	}
	else
	{
		Color color;

		color.r = 0;
		color.g = 0;
		color.b = 0;

		m_Edge.setOutlineColor(color);

		isEdge = false;
	}
}
