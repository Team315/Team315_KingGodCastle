#include "WarriorsHeart.h"

WarriorsHeart::WarriorsHeart(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "WarriorsHeart"; // ������ ����
}

WarriorsHeart::~WarriorsHeart()
{
}