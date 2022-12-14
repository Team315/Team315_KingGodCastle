#include "HeroOfSalvation.h"

HeroOfSalvation::HeroOfSalvation(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "HeroOfSalvation"; // 구원의 영웅
}

HeroOfSalvation::~HeroOfSalvation()
{
}
