#include "TilePlay.h"

TilePlay::TilePlay()
	:isCollAble(false), onTileObj(nullptr)
{
	//m_TileData = { {0,0},-1,-1,-1 };
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

void TilePlay::SetTilePlay(Vector2i indexArr, Vector2f pos, int index, TileTypes TileTypes = TileTypes::None, int grade = 0)
{
	m_index = indexArr;
	m_TileTypes = TileTypes;

	m_TileData.arrIndex = indexArr;
	m_TileData.TileTypes = (int)TileTypes;
	m_TileData.ThemeTypes = 0;
	m_TileData.pathIndex = index;
	m_TileData.grade = grade;

	if (index % 2 == 0)
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
	m_TileData.ThemeTypes= (int)themeTypes;
	m_TileData.TileTypes = (int)TileTypes::Obatacle;
	m_TileData.pathIndex = obstacleIndex;
	m_TileTypes = TileTypes::Obatacle;

	m_Obj.setTexture(*RESOURCE_MGR->GetTexture(SetObstaclePath(themeTypes, obstacleIndex)), true);
	m_Obj.setPosition(GetPos());
	CLOG::PrintVectorState(GetPos(), "방금 놓은 장애물 포스");
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

void TilePlay::SetMonster(ThemeTypes themeTypes, int monsterIndex, int grade)
{
	m_TileData.ThemeTypes=(int)themeTypes;
	m_TileData.TileTypes = (int)TileTypes::Monster;
	m_TileData.pathIndex = monsterIndex;
	m_TileData.grade = grade;
	m_TileTypes = TileTypes::Monster;

	m_Obj.setTexture(*RESOURCE_MGR->GetTexture(SetMonsterPath(themeTypes, monsterIndex)), true);
	m_Obj.setPosition(GetPos());

	CLOG::PrintVectorState(GetPos(), "방금 놓은 몬스터 포스");

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
	m_TileData.TileTypes = (int)TileTypes::None;

	m_TileTypes = TileTypes::None;
}

void TilePlay::SetTileData(ns::TileData TileData)
{
	if (TileData.TileTypes != 3)
		SetEraser();

	if (TileData.TileTypes == 1)
	{
		SetObstacle((ThemeTypes)TileData.ThemeTypes, TileData.pathIndex);
	}
	else if (TileData.TileTypes == 2)
	{

		SetMonster((ThemeTypes)TileData.ThemeTypes, TileData.pathIndex, TileData.grade);

	}
}

void TilePlay::SetOnTileObj(Object* onTileObj)
{
	this->onTileObj = onTileObj;
}

Object* TilePlay::GetOnTileObj()
{
	return onTileObj;
}

TileInfo TilePlay::GetTileInfo()
{
	return m_TileInfo;
}

TileData TilePlay::GetTileData()
{
	return m_TileData;
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