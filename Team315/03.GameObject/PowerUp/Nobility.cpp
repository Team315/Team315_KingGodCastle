#include "Nobility.h"

Nobility::Nobility(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false)
{
	type = "PowerUp";
	name = "Nobility"; // ����
}

Nobility::~Nobility()
{
}