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