#include "WarriorsHeart.h"

WarriorsHeart::WarriorsHeart(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "WarriorsHeart"; // 전사의 심장
}

WarriorsHeart::~WarriorsHeart()
{
}