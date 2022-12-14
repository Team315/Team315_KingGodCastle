#include "Vampire.h"

Vampire::Vampire(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "Vampire"; // ÈíÇ÷±Í
}

Vampire::~Vampire()
{
}
