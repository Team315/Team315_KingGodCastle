#include "Meditation.h"

Meditation::Meditation(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false)
{
	type = "PowerUp";
	name = "Meditation"; // Έν»σ
}

Meditation::~Meditation()
{
}