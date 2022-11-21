#include "Obstacle.h"
#include "Include.h"

Obstacle::Obstacle(string path)
{
	star->SetStarNumber(0);
	star->SetActive(false);
	hpBar->SetActive(false);
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