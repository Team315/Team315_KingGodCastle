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
	window.draw(m_Edge);
	window.draw(sprite);
}

void SelectObstacle::SetSelectObstacle(Vector2f pos, ThemeTypes types, int index)
{
	m_index = index;
	sprite.setTexture(*RESOURCE_MGR->GetTexture(SetPath(types, m_index)));
	sprite.setPosition(pos);
	SetOrigin(Origins::MC);

	FloatRect rect = sprite.getGlobalBounds();
	m_Edge.setSize({ rect.width,rect.height });
	m_Edge.setFillColor(Color::White);
	m_Edge.setPosition(pos);
	m_Edge.setOutlineThickness(-4.f);
	Utils::SetOrigin(m_Edge, Origins::MC);
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

int SelectObstacle::GetIndex()
{
	return m_index;
}

bool SelectObstacle::CollisionCheck(Vector2f pos, int index)
{
	return ChangeColor(sprite.getGlobalBounds().contains(pos));

}

bool SelectObstacle::ChangeColor(bool check)
{
	if (check)
	{
		Color color;

		color.r = 255;
		color.g = 255;
		color.b = 255;

		m_Edge.setFillColor(color);
		return true;
	}
	else
	{
		Color color;
		color.r = 0;
		color.g = 0;
		color.b = 0;

		m_Edge.setFillColor(color);
		return false;
	}
}

void SelectObstacle::OnEdge(int index)
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
