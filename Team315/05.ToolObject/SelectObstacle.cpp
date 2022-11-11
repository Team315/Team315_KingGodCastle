#include "SelectObstacle.h"

SelectObstacle::SelectObstacle()
	:m_types(ThemeTypes::Goblin)
{
}

SelectObstacle::~SelectObstacle()
{
}

void SelectObstacle::Init()
{
}

void SelectObstacle::Release()
{
}

void SelectObstacle::Update(float dt)
{
}

void SelectObstacle::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void SelectObstacle::SetSelectObstacle(Vector2f pos, ThemeTypes types, int index)
{
	m_index = index;
	sprite.setTexture(*RESOURCE_MGR->GetTexture(SetPath(types, m_index)));
	sprite.setPosition(pos);
	SetOrigin(Origins::MC);
}

string SelectObstacle::SetPath(ThemeTypes types, int num)
{
	m_index = num;
	string field = to_string((int)types / 10) + to_string((int)types % 10);

	string path = "graphics/TileSet/obstacle_" + field + "/obstacle_" + field + "_";
	string sNum = to_string(m_index / 10) + to_string(m_index % 10);
	string png = ".png";

	return path + sNum + png;
}
