#include "WarriorsHeart.h"

WarriorsHeart::WarriorsHeart(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false)
{
	type = "PowerUp";
	name = "WarriorsHeart"; // ������ ����
}

WarriorsHeart::~WarriorsHeart()
{
}