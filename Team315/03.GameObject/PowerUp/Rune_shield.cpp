#include "Rune_shield.h"

Rune_shield::Rune_shield(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Rune_shield"; // ∑È πÊ∆–
}

Rune_shield::~Rune_shield()
{
}
