#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Init()
{
}

void Tile::Release()
{
}

void Tile::Update(float dt)
{
}

void Tile::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);

	if (m_tileData.TileTypes == (int)TileTypes::PlayerArea)
		window.draw(m_playerArea);
}

void Tile::CreateTile(ns::TileData tileData)
{
	m_tileData = tileData;

	if ((m_tileData.arrIndex.x + m_tileData.arrIndex.y) % 2 == 0)
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/TileSet/Field_00.png"));
	else
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/TileSet/Field_01.png"));

	Color color = sprite.getColor();
	color.a = 30;
	sprite.setColor(color);

	Vector2i reverseArrPos = { m_tileData.arrIndex.y, m_tileData.arrIndex.x };
	SetPos(GAME_MGR->IdxToPos(reverseArrPos));
	SetOrigin(Origins::BC);

	if (m_tileData.TileTypes == (int)TileTypes::PlayerArea)
	{
		m_playerArea.setSize(GetSize());
		m_playerArea.setScale(0.97f, 0.97f);
		m_playerArea.setFillColor({ 0,0,0,0 });
		m_playerArea.setOutlineThickness(-2.f);
		m_playerArea.setOutlineColor({ 255,255,255,30 });
		m_playerArea.setPosition(GetPos());
		Utils::SetOrigin(m_playerArea, Origins::BC);
	}
}

string Tile::GetObstaclePath()
{
	string field = to_string(m_tileData.ThemeTypes / 10) + to_string(m_tileData.ThemeTypes % 10);
	string path = "graphics/TileSet/obstacle_" + field + "/obstacle_" + field + "_";
	path += to_string(m_tileData.pathIndex / 10) + to_string(m_tileData.pathIndex % 10) + ".png";
	return path;
}

string Tile::GetMonsterName()
{
	string name = "";
	switch (m_tileData.ThemeTypes)
	{
	case (int) ThemeTypes::Goblin:
		name = "Goblin";
		break;
	case (int) ThemeTypes::Thief:
		name = "Thief";
		break;
	case (int) ThemeTypes::Slime:
		name = "Slime";
		break;
	default:
		break;
	}
	name += to_string(m_tileData.pathIndex / 10) + to_string(m_tileData.pathIndex % 10);
	return name;
}