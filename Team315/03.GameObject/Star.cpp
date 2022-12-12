#include "Star.h"
#include "Include.h"

Star::Star(bool mode, bool useExtraUpgrade, int starNumber)
	: starNumber(starNumber)
{
	if (starNumber == 0)
		CalculateRandomChance(mode, useExtraUpgrade);
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

bool Star::CalculateRandomChance(bool mode, bool useExtraUpgrade)
{
	starNumber++;
	if (!useExtraUpgrade)
		return false;

	float percent = 0.f;
	if (mode)
		percent = GAME_MGR->GetExtraLevelUpCombinate();
	else
		percent = GAME_MGR->GetExtraLevelUpSummon();

	bool ret = false;
	if (starNumber < STAR_MAX - 1)
	{
		ret = Utils::RandomRange(0, 100) < percent;
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