#include "Star.h"
#include "Include.h"

Star::Star(bool mode, bool fixedStar, int starNumber)
	: starNumber(starNumber)
{
	if (starNumber == 0)
		CalculateRandomChance(mode, fixedStar);
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

bool Star::CalculateRandomChance(bool mode, bool fixedStar)
{
	starNumber++;
	if (fixedStar)
		return false;

	float probabilty = 0.f;
	if (mode)
		probabilty = GAME_MGR->GetExtraLevelUpCombinate();
	else
		probabilty = GAME_MGR->GetExtraLevelUpSummon();

	bool ret = false;
	if (starNumber < STAR_MAX - 1)
	{
		ret = Utils::RandomRange(0, 100) < probabilty ? true : false;
		if (starNumber < STAR_MAX)
			starNumber = ret ? starNumber + 1 : starNumber;
	}
	return ret;
}

void Star::UpdateTexture()
{
	string path = "graphics/commonUI/" + ("Level_Star_" + to_string(starNumber) + ".png");
	sprite.setTexture(*RESOURCE_MGR->GetTexture(path), true);
	SpriteObj::SetOrigin(Origins::BC);
}