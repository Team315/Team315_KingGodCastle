#include "Meditation.h"

Meditation::Meditation(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, true, false)
{
	type = "PowerUp";
	name = "Meditation"; // ���
}

Meditation::~Meditation()
{
}