#include "Comrade.h"

Comrade::Comrade(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Comrade"; // ����
}

Comrade::~Comrade()
{
}