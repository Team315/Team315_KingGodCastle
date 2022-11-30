#include "Obstacle.h"

Obstacle::Obstacle(string path)
{
	SetTexture(*RESOURCE_MGR->GetTexture(path));

	SetName("Obstacle");
	SetType("Obstacle"); 
	SetOrigin(Origins::BC);
}

Obstacle::~Obstacle()
{
}

void Obstacle::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Obstacle::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
}