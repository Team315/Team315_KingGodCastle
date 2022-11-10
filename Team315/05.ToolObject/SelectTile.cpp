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
}

void SelectTile::SetSelectTile(Vector2f pos, ThemeTypes types, int index)
{
	m_index = index;
	//SetTexture(*RESOURCE_MGR->GetTexture(SetPath(m_index)));
	sprite.setTexture(*RESOURCE_MGR->GetTexture(SetPath(types, m_index)));
	sprite.setPosition(pos);
	SetOrigin(Origins::MC);
}

string SelectTile::SetPath(ThemeTypes types, int num)
{
	m_index = num;
	string field = to_string((int)types / 10) + to_string((int)types % 10);

	string path = "graphics/TileSet/Field_" + field + "/field_"+ field+"_";
	string sNum = to_string(m_index / 10) + to_string(m_index % 10);
	string png = ".png";

	return path + sNum + png;
}