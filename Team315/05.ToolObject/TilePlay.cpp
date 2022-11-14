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
		window.draw(m_Obstacle);
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
		break;
	case TileTypes::Obatacle:
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
