#include "ExecutionerSoul.h"

ExecutionerSoul::ExecutionerSoul(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "ExecutionerSoul"; // ������ ��ȥ
}

ExecutionerSoul::~ExecutionerSoul()
{
}