#include "Star.h"
#include "Include.h"

Star::Star()
	: inBattle(false)
{
	starNumber = Utils::RandomRange(0, 100) < GAME_MGR->GetExtraLevelUpChance() ?
		2 : 1;
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

void Star::UpdateTexture()
{
	string path = "graphics/commonUI/";
	path += inBattle ? "Level_Bar_" : "Level_Star_";
	path += to_string(starNumber) + ".png";
	sprite.setTexture(*RESOURCE_MGR->GetTexture(path), true);
}