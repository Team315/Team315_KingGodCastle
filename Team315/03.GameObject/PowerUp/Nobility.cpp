#include "Nobility.h"

Nobility::Nobility(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "Nobility"; // ±Õ¡∑
}

Nobility::~Nobility()
{
}