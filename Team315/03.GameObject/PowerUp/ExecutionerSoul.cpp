#include "ExecutionerSoul.h"

ExecutionerSoul::ExecutionerSoul(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "ExecutionerSoul"; // ������ ��ȥ
}


ExecutionerSoul::~ExecutionerSoul()
{
}