#include "Comrade.h"

Comrade::Comrade(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "Comrade"; // Àü¿ì
}

Comrade::~Comrade()
{
}