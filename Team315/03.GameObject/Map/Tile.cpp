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

	switch ((TileTypes)m_tileData.TileTypes)
	{
	case TileTypes::None:
		break;
	case TileTypes::Obatacle:
	case TileTypes::Monster:
		window.draw(m_obstacle);
		break;
	case TileTypes::PlayerArea:
		window.draw(m_playerArea);
		break;
	}
}

void Tile::CreateTile(ns::TileData tileData)
{
	m_tileData = tileData;

	if ((m_tileData.arrIndex.x + m_tileData.arrIndex.y) % 2 == 0)
	{
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/TileSet/Field_00.png"));
		Color color = sprite.getColor();
		color.a = 30;
		sprite.setColor(color);
	}
	else
	{
		SetTexture(*RESOURCE_MGR->GetTexture("graphics/TileSet/Field_01.png"));
		Color color = sprite.getColor();
		color.a = 30;
		sprite.setColor(color);
	}

	m_pos = { TILE_SIZE + (TILE_SIZE /** 0.5f*/) + (m_tileData.arrIndex.y * TILE_SIZE),
				10.f+TILE_SIZE + (m_tileData.arrIndex.x * TILE_SIZE) };
	SetPos(m_pos);
	SetOrigin(Origins::BC);

	switch ((TileTypes)m_tileData.TileTypes)
	{
	case TileTypes::None:
		break;
	case TileTypes::Obatacle:
		SetObstacle((ThemeTypes)m_tileData.ThemeTypes, m_tileData.pathIndex);
		break;
	case TileTypes::Monster:
		SetMonster((ThemeTypes)m_tileData.ThemeTypes, m_tileData.pathIndex, m_tileData.grade);
		break;
	case TileTypes::PlayerArea:
		m_playerArea.setSize(GetSize());
		m_playerArea.setScale(0.97f, 0.97f);
		m_playerArea.setFillColor({ 0,0,0,0 });
		m_playerArea.setOutlineThickness(-2.f);
		m_playerArea.setOutlineColor({ 255,255,255,30 });
		m_playerArea.setPosition(GetPos());
		Utils::SetOrigin(m_playerArea, Origins::BC);
		break;
	}
}

void Tile::SetObstacle(ThemeTypes themeTypes, int obstacleIndex)
{
	m_obstacle.setTexture(*RESOURCE_MGR->GetTexture(SetObstaclePath(themeTypes, obstacleIndex)), true);
	m_obstacle.setPosition(GetPos());
	Utils::SetOrigin(m_obstacle, Origins::BC);
}

string Tile::SetObstaclePath(ThemeTypes types, int num)
{
	string field = to_string((int)types / 10) + to_string((int)types % 10);

	string path = "graphics/TileSet/obstacle_" + field + "/obstacle_" + field + "_";
	string sNum = to_string(num / 10) + to_string(num % 10);
	string png = ".png";

	return path + sNum + png;
}

void Tile::SetMonster(ThemeTypes themeTypes, int monsterIndex, int grade)
{
	m_obstacle.setTexture(*RESOURCE_MGR->GetTexture(SetMonsterPath(themeTypes, monsterIndex)), true);
	m_obstacle.setPosition(GetPos());

	Utils::SetOrigin(m_obstacle, Origins::BC);
}

string Tile::SetMonsterPath(ThemeTypes types, int num)
{
	string path;

	if (num == 0)
	{
		path = "graphics/ToolUi/monster/Boss";
	}
	else
	{
		path = "graphics/ToolUi/monster/Monster";
	}

	string field = to_string((int)types / 10) + to_string((int)types % 10) + "_";
	string sNum = to_string(num / 10) + to_string(num % 10);
	string png = ".png";

	return path + field + sNum + png;
}
