#include "TileBackground.h"

TileBackground::TileBackground()
	:m_isCollAble(false)
{
	backGroundData.pathIndex = 0;
	backGroundData.ThemeTypes = 0;
}

TileBackground::~TileBackground()
{
}

void TileBackground::Init()
{
}

void TileBackground::Release()
{
}

void TileBackground::Update(float dt)
{
}

void TileBackground::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	if(m_isCollAble)
		m_rectHit.Draw(window);
}

void TileBackground::SetTileBackground(Vector2i indexArr, Vector2f pos, int chapter)
{
	backGroundData.arrIndex = indexArr;
	backGroundData.ThemeTypes =  chapter;
	backGroundData.TileTypes = (int)TileTypes::BackGround;
	backGroundData.pathIndex = -1;
	m_ThemeTypes = (ThemeTypes)chapter;
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/TileSet/Field_02.png"));
	SetPos(pos);
	SetOrigin(Origins::TL);

	m_rectHit.SetSize(TILE_SIZE, TILE_SIZE);
	m_rectHit.SetPos(pos);
	
	m_rectHit.SetFillColor({0,0,0,0});
	m_rectHit.SetOutline(Color::Red, -1.f);
	//SetHitbox(GetGlobalBounds(), Origins::TL, -1, -1);
	//SetHitBoxActive( true);
}

void TileBackground::LoadTileBackground(ns::BackGroundData Data)
{
	backGroundData.arrIndex = Data.arrIndex;
	backGroundData.ThemeTypes = Data.ThemeTypes;
	backGroundData.pathIndex = Data.pathIndex;
	backGroundData.TileTypes = Data.TileTypes;
	m_ThemeTypes = (ThemeTypes)Data.ThemeTypes;

	sprite.setTexture(*RESOURCE_MGR->GetTexture(GetBackgroundPath((ThemeTypes)backGroundData.ThemeTypes, backGroundData.pathIndex)), true);
	SetOrigin(Origins::TL);
}

bool TileBackground::CollisionCheck(Vector2f pos)
{
	return OnEdge(sprite.getGlobalBounds().contains(pos));

}

bool TileBackground::OnEdge(bool isCollAble)
{
	if (isCollAble)
		m_isCollAble = true;
	else
		m_isCollAble = false;

	return isCollAble;
}

void TileBackground::ChangeTileBackground(ThemeTypes types, int index)
{
	backGroundData.ThemeTypes = (int)types;
	backGroundData.pathIndex = index;
	m_TileTypes = TileTypes::BackGround;

	
	sprite.setTexture(*RESOURCE_MGR->GetTexture(GetBackgroundPath(types, index)), true);
	SetOrigin(Origins::TL);
	CLOG::PrintVectorState(GetPos(), "방금 놓은 타일 포스");
	cout << backGroundData.ThemeTypes << " " << backGroundData.pathIndex << endl;
}

string TileBackground::GetBackgroundPath(ThemeTypes types, int num)
{
	string field = to_string((int)types / 10) + to_string((int)types % 10);

	string path = "graphics/TileSet/Field_" + field + "/field_" + field + "_";
	string sNum = to_string(num / 10) + to_string(num % 10);
	string png = ".png";
	if (num == -1)
	{
		return "graphics/TileSet/Field_02.png";
	}
	return path + sNum + png;
}
