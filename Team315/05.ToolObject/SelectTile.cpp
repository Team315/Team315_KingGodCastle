#include "SelectTile.h"

SelectTile::SelectTile()
	:m_types(ThemeTypes::Goblin)
{
}

SelectTile::~SelectTile()
{
}

void SelectTile::Init()
{
}

void SelectTile::Release()
{
}

void SelectTile::Update(float dt)
{
}

void SelectTile::Draw(RenderWindow& window)
{
	
	window.draw(sprite);
	window.draw(m_Edge);
}

void SelectTile::SetSelectTile(Vector2f pos, ThemeTypes types, int index)
{
	m_index = index;
	m_types = types;

	sprite.setTexture(*RESOURCE_MGR->GetTexture(SetPath(m_types, m_index)));
	sprite.setPosition(pos);
	SetOrigin(Origins::MC);


	FloatRect rect = sprite.getGlobalBounds();
	Color color = { 0,0,0,0 };
	m_Edge.setSize({ rect.width,rect.height });
	m_Edge.setFillColor(color);
	m_Edge.setPosition(pos);
	m_Edge.setOutlineThickness(-4.f);
	Utils::SetOrigin(m_Edge, Origins::MC);
}

string SelectTile::SetPath(ThemeTypes types, int num)
{
	string field = to_string((int)types / 10) + to_string((int)types % 10);
	string path = "graphics/TileSet/Field_" + field + "/field_"+ field+"_";
	string sNum = to_string(m_index / 10) + to_string(m_index % 10);
	string png = ".png";

	return path + sNum + png;
}

int SelectTile::GetIndex()
{
	return m_index;
}

ThemeTypes SelectTile::GetThemeTypes()
{
	return m_types;
}

bool SelectTile::CollisionCheck(Vector2f pos, int index)
{
	return ChangeColor(sprite.getGlobalBounds().contains(pos));
}

bool SelectTile::ChangeColor(bool check)
{
	if (check)
	{
		Color color = {255,255,255,80};

		//color.r = 255;
		//color.g = 255;
		//color.b = 255;

		m_Edge.setFillColor(color);
		return true;
	}
	else
	{
		Color color = { 0,0,0,0 };
		//color.r = 0;
		//color.g = 0;
		//color.b = 0;

		m_Edge.setFillColor(color);

		return false;
	}
}

void SelectTile::OnEdge(int index)
{
	if (m_index == index)
	{
		Color color= { 0,0,255 };

		//color.b = 255;

		m_Edge.setOutlineColor(color);
		isEdge = true;
	}
	else
	{
		Color color = { 0,0,0,0};

		m_Edge.setOutlineColor(color);
		isEdge = false;
	}
}
