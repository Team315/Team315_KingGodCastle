#include "Meditation.h"

Meditation::Meditation(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "Meditation"; // Έν»σ
}

Meditation::~Meditation()
{
}