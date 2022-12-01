#include "TileBackground.h"

TileBackground::TileBackground()
{
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
	Update(dt);
}

void TileBackground::Draw(RenderWindow& window)
{
	Draw(window);
}

void TileBackground::SetTilePlay(Vector2i indexArr, Vector2f pos, int index, TileTypes TileTypes)
{
	backGroundData.arrIndex = indexArr;
	backGroundData.pathIndex = index;
	backGroundData.TileTypes = (int)TileTypes;
	backGroundData.ThemeTypes = 0;

	SetTexture(*RESOURCE_MGR->GetTexture("graphics/TileSet/Field_02.png"));
	SetOrigin(Origins::MC);
	SetPos(pos);
	

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
