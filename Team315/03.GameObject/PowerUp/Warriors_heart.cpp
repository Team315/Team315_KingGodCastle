#include "Warriors_heart.h"

Warriors_heart::Warriors_heart(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Warriors_heart"; // ������ ����
}

Warriors_heart::~Warriors_heart()
{
}