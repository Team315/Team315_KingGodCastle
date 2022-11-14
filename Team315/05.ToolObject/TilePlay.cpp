#include "TilePlay.h"
#include "Include.h"

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
}

void TilePlay::SetTilePlay(Vector2i index, Vector2f pos, int count)
{
	m_index = index;

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
}
