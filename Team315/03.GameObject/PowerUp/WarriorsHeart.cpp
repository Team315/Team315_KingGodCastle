#include "WarriorsHeart.h"

WarriorsHeart::WarriorsHeart(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "WarriorsHeart"; // 전사의 심장
}

WarriorsHeart::~WarriorsHeart()
{
}