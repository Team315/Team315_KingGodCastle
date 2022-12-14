#include "Comrade.h"

Comrade::Comrade(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "Comrade"; // Àü¿ì
}

Comrade::~Comrade()
{
}