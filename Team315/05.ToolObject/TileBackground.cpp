#include "TileBackground.h"
#include "RectangleObj.h."

TileBackground::TileBackground()
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
	m_rectHit.Draw(window);
}

void TileBackground::SetTileBackground(Vector2i indexArr, Vector2f pos)
{
	backGroundData.arrIndex = indexArr;

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

bool TileBackground::CollisionCheck(Vector2f pos, int index)
{
	if (!isCollAble)
		return false;

	return OnEdge(sprite.getGlobalBounds().contains(pos));
}

bool TileBackground::OnEdge(bool isCollAble)
{
	return false;
}
