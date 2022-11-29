#include "Star.h"
#include "Include.h"

Star::Star(int starNumber)
	: starNumber(starNumber)
{
	if (starNumber == 0)
		CalculateRandomChance();
	UpdateTexture();
}

Star::~Star()
{
}

void Star::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Star::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
}

bool Star::CalculateRandomChance()
{
	bool ret = false;
	if (starNumber < 6)
		ret = Utils::RandomRange(0, 100) < GAME_MGR->GetExtraLevelUpChance() ? true : false;
	if (starNumber != 7)
		starNumber = ret ? starNumber + 2 : starNumber + 1;
	return ret;
}

void Star::UpdateTexture()
{
	string path = "graphics/commonUI/" + ("Level_Star_" + to_string(starNumber) + ".png");
	sprite.setTexture(*RESOURCE_MGR->GetTexture(path), true);
	SpriteObj::SetOrigin(Origins::BC);
}