#include "ExecutionerSoul.h"

ExecutionerSoul::ExecutionerSoul(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "ExecutionerSoul"; // 집행자 영혼
}


ExecutionerSoul::~ExecutionerSoul()
{
}