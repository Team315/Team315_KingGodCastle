#include "HeroOfSalvation.h"

HeroOfSalvation::HeroOfSalvation(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "HeroOfSalvation"; // ������ ����
}

HeroOfSalvation::~HeroOfSalvation()
{
}
