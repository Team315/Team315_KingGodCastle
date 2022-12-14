#include "Warriors_heart.h"

Warriors_heart::Warriors_heart(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Warriors_heart"; // 전사의 심장
}

Warriors_heart::~Warriors_heart()
{
}