#include "ExecutionerSoul.h"

ExecutionerSoul::ExecutionerSoul(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, true, true)
{
	type = "PowerUp";
	name = "ExecutionerSoul"; // ������ ��ȥ
}

ExecutionerSoul::~ExecutionerSoul()
{
}