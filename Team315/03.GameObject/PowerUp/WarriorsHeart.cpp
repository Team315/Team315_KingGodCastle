#include "WarriorsHeart.h"

WarriorsHeart::WarriorsHeart(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "WarriorsHeart"; // ������ ����
}

WarriorsHeart::~WarriorsHeart()
{
}