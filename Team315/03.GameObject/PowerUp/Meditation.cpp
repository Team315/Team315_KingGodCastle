#include "Meditation.h"

Meditation::Meditation(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Meditation"; // ���
}

Meditation::~Meditation()
{
}