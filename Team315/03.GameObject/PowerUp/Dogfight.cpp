#include "Dogfight.h"

Dogfight::Dogfight(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Dogfight"; // °³½Î¿ò
}

Dogfight::~Dogfight()
{
}