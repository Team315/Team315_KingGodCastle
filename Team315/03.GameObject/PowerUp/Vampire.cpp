#include "Vampire.h"

Vampire::Vampire(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, true, false)
{
	type = "PowerUp";
	name = "Vampire"; // ÈíÇ÷±Í
}

Vampire::~Vampire()
{
}
