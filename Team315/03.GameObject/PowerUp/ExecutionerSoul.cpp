#include "ExecutionerSoul.h"

ExecutionerSoul::ExecutionerSoul(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "ExecutionerSoul"; // ������ ��ȥ
}

ExecutionerSoul::~ExecutionerSoul()
{
}