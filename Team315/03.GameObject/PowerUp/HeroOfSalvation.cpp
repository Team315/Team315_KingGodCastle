#include "HeroOfSalvation.h"

HeroOfSalvation::HeroOfSalvation(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "HeroOfSalvation"; // ������ ����
}

HeroOfSalvation::~HeroOfSalvation()
{
}