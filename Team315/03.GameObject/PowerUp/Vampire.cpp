#include "Vampire.h"

Vampire::Vampire(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Vampire"; // ÈíÇ÷±Í
}

Vampire::~Vampire()
{
}
