#include "Nobility.h"

Nobility::Nobility(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Nobility"; // ±Õ¡∑
}

Nobility::~Nobility()
{
}