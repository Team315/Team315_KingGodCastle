#include "ExecutionerSoul.h"

ExecutionerSoul::ExecutionerSoul(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "ExecutionerSoul"; // 집행자 영혼
}

ExecutionerSoul::~ExecutionerSoul()
{
}