#include "HeroOfSalvation.h"

HeroOfSalvation::HeroOfSalvation(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Comrade"; // Àü¿ì
}

HeroOfSalvation::~HeroOfSalvation()
{
}
