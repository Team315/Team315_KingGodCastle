#include "Dogfight.h"

Dogfight::Dogfight(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Dogfight"; // ���ο�
}

Dogfight::~Dogfight()
{
}