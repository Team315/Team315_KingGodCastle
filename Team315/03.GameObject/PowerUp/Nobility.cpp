#include "Nobility.h"

Nobility::Nobility(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, false)
{
	type = "PowerUp";
	name = "Nobility"; // ±Õ¡∑
}

Nobility::~Nobility()
{
}