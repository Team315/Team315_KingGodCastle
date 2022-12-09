#include "Brazier.h"

Brazier::Brazier()
	:m_grade(0)
{
}

Brazier::~Brazier()
{
}

void Brazier::Init()
{
	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/Altar_Brazier.png"));
	Vector2f vec = { GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT * 0.8f };
	SetPos(vec);
}

void Brazier::Release()
{

}

void Brazier::Update(float dt)
{
}

void Brazier::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Brazier::MoveSetPos(Vector2f movepos)
{
	SetPos(movepos);
}
