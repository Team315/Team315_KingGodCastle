#include "Comrade.h"

Comrade::Comrade(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "Comrade"; // ����
}

Comrade::~Comrade()
{
}