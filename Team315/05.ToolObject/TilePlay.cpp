#include "TilePlay.h"

TilePlay::TilePlay()
	:isCollAble(false)
{
}

TilePlay::~TilePlay()
{
}

void TilePlay::Init()
{
}

void TilePlay::Release()
{
}

void TilePlay::Update(float dt)
{
}

void TilePlay::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);

	switch (m_TileTypes)
	{
	case TileTypes::None:
		break;
	case TileTypes::Obatacle:
	case TileTypes::Monster:
		window.draw(m_Obj);
		break;
	case TileTypes::PlayerArea:
		window.draw(m_playerArea);
		break;
	}
}

void TilePlay::SetTilePlay(Vector2i index, Vector2f pos, int count, TileTypes TileTypes)
{
	m_index = index;
	m_TileTypes = TileTypes;

	if (count % 2 == 0)
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
	SetPos(pos);
	SetOrigin(Origins::BC);

	switch (m_TileTypes)
	{
	case TileTypes::None:
		isCollAble = true;
		break;
	case TileTypes::Obatacle:
		isCollAble = true;
		break;
	case TileTypes::Monster:
		isCollAble = true;
		break;
	case TileTypes::PlayerArea:
		m_playerArea.setSize(GetSize());
		m_playerArea.setScale(0.97f, 0.97f);
		m_playerArea.setFillColor({ 0,0,0,0 });
		m_playerArea.setOutlineThickness(-2.f);
		m_playerArea.setOutlineColor({255,255,255,30});
		m_playerArea.setPosition(GetPos());
		Utils::SetOrigin(m_playerArea, Origins::BC);
		break;
	}
}

void TilePlay::SetObstacle(ThemeTypes themeTypes, int obstacleIndex)
{
	m_TileTypes = TileTypes::Obatacle;
	m_Obj.setTexture(*RESOURCE_MGR->GetTexture(SetObstaclePath(themeTypes, obstacleIndex)), true);
	m_Obj.setPosition(GetPos());
	cout << GetPos().x << " " << GetPos().y << endl;
	Utils::SetOrigin(m_Obj, Origins::BC);
}

string TilePlay::SetObstaclePath(ThemeTypes types, int num)
{
	string field = to_string((int)types / 10) + to_string((int)types % 10);

	string path = "graphics/TileSet/obstacle_" + field + "/obstacle_" + field + "_";
	string sNum = to_string(num / 10) + to_string(num % 10);
	string png = ".png";

	return path + sNum + png;
}

void TilePlay::SetMonster(ThemeTypes themeTypes, int monsterIndex)
{
	m_TileTypes = TileTypes::Monster;

	m_Obj.setTexture(*RESOURCE_MGR->GetTexture(SetMonsterPath(themeTypes, monsterIndex)), true);
	m_Obj.setPosition(GetPos());
	cout << GetPos().x << " " << GetPos().y << endl;

	Utils::SetOrigin(m_Obj, Origins::BC);
}

string TilePlay::SetMonsterPath(ThemeTypes types, int num)
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

void TilePlay::SetEraser()
{
	m_TileTypes = TileTypes::None;
}

bool TilePlay::CollisionCheck(Vector2f pos, int index)
{
	if (!isCollAble)
		return false;

	return ChangeAlpha(sprite.getGlobalBounds().contains(pos));
}

bool TilePlay::ChangeAlpha(bool check)
{
	if (check)
	{
		Color color = sprite.getColor();
		color.a = 100;
		sprite.setColor(color);
		return true;
	}
	else
	{
		Color color = sprite.getColor();
		color.a = 30;
		sprite.setColor(color);
		return false;
	}
}
