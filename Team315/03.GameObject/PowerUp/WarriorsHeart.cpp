#include "WarriorsHeart.h"

WarriorsHeart::WarriorsHeart(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, true, false)
{
	type = "PowerUp";
	name = "WarriorsHeart"; // ������ ����
}

WarriorsHeart::~WarriorsHeart()
{
}